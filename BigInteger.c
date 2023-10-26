#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "BigInteger.h"

// Function to initialize a BigInteger
struct BigInteger initialize(char *s)
{
    struct BigInteger n;
    n.head = NULL;
    n.num = 0;
    n.sign = 1; // positive

    if (s[0] == '-')
    {
        n.sign = -1;
        s++; // Skip the '-' sign
    }

    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        int val = s[i] - '0';
        addDigit(&n, val);
    }

    return n;
}

// Function to add a digit to the linked list (stores in reverse order of input)
void addDigit(struct BigInteger *n, int val)
{
    Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->digit = val;
    temp->next = NULL;

    if (n->head == NULL)
    {
        n->head = temp;
        return;
    }

    Node *itr = n->head;
    while (itr->next != NULL)
    {
        itr = itr->next;
    }
    itr->next = temp;
    n->num++;
}
// Function to reverse and display a linked list of digits
void reverseAndDisplay(struct Node *head)
{
    if (head == NULL)
        return;
    reverseAndDisplay(head->next);
    printf("%d", head->digit);
}

// Function to reverse and display a BigInteger
void display(struct BigInteger n)
{
    if (n.head == NULL)
    {
        printf("0\n");
        return;
    }
    if (n.sign == -1)
    {
        printf("-");
    }

    reverseAndDisplay(n.head);
    printf("\n");
}

// Function to add two BigIntegers

struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    res.head = NULL;
    res.num = 0;

    if (a.sign == -1 && b.sign == 1)
    {

        a.sign = 1;
        res = sub(a, b);
        a.sign = -1;
    }
    else if (a.sign == 1 && b.sign == -1)
    {

        b.sign = 1;
        res = sub(a, b);
        b.sign = -1;
    }
    else if (a.sign == -1 && b.sign == -1)
    {

        a.sign = 1;
        b.sign = 1;
        res = add(a, b);
        res.sign = -1;
    }
    else
    {

        int carry = 0;
        Node *p1 = a.head;
        Node *p2 = b.head;

        while (p1 != NULL || p2 != NULL || carry > 0)
        {
            int sum = carry;
            if (p1 != NULL)
            {
                sum += p1->digit;
                p1 = p1->next;
            }
            if (p2 != NULL)
            {
                sum += p2->digit;
                p2 = p2->next;
            }

            carry = sum / 10; // finds the carry
            addDigit(&res, sum % 10);
        }
    }

    return res;
}

// Function to subtract two big integers
struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    res.head = NULL;
    res.num = 0;

    if (a.sign == -1 && b.sign == 1)
    {
        // If a is negative and b is positive, result is negative
        a.sign = 1;
        res = add(a, b);
        res.sign = -1;
    }
    else if (a.sign == 1 && b.sign == -1)
    {
        // If a is positive and b is negative, result is positive
        b.sign = 1;
        res = add(a, b);
    }
    else if (a.sign == -1 && b.sign == -1)
    {
        // If both are negative, reverse and subtract
        a.sign = 1;
        b.sign = 1;
        res = sub(b, a);
    }
    else
    {
        // Both are positive, perform subtraction
        struct Node *p1 = a.head;
        struct Node *p2 = b.head;
        int borrow = 0;

        while (p1 != NULL || p2 != NULL)
        {
            int val1 = (p1 != NULL) ? p1->digit : 0;
            int val2 = (p2 != NULL) ? p2->digit : 0;
            int diff = val1 - val2 - borrow;

            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            addDigit(&res, diff);

            if (p1 != NULL)
            {
                p1 = p1->next;
            }
            if (p2 != NULL)
            {
                p2 = p2->next;
            }
        }

        // Remove leading zeros
        while (res.head != NULL && res.head->digit == 0)
        {
            struct Node *temp = res.head;
            res.head = res.head->next;
            free(temp);
            res.num--;
        }

        res.sign = 1;
    }

    return res;
}

// to find length of linked list
int length(struct BigInteger a)
{
    int i = 0;
    while (a.head != NULL)
    {
        i++;
        a.head = (a.head)->next;
    }
    return i;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    // Initialize the result to 0
    struct BigInteger res;
    res.head = NULL;
    res.num = 0;
    res.sign = (a.sign * b.sign);

    if (a.head->digit == 0 || b.head->digit == 0)
    {
        return res; // Multiplying by 0, result is 0
    }

    int i = 0;
    Node *p2 = b.head;

    while (p2 != NULL)
    {
        struct BigInteger temp;
        temp.head = NULL;
        temp.num = 0;
        temp.sign = 1;

        for (int j = 0; j < i; j++)
        {
            addDigit(&temp, 0);
        }

        int carry = 0;
        Node *p1 = a.head;

        while (p1 != NULL || carry > 0)
        {
            int product = carry;

            if (p1 != NULL)
            {
                product += p1->digit * p2->digit;
                p1 = p1->next;
            }

            carry = product / 10;
            addDigit(&temp, product % 10);
        }

        res = add(res, temp);

        p2 = p2->next;
        i++;
    }

    return res;
}

// Function to compare the values of two BigIntegers
int compare(struct BigInteger a, struct BigInteger b)
{
    // Remove leading zeros
    while (a.head != NULL && a.head->digit == 0)
    {
        struct Node *temp = a.head;
        a.head = a.head->next;
        free(temp);
        a.num--;
    }

    while (b.head != NULL && b.head->digit == 0)
    {
        struct Node *temp = b.head;
        b.head = b.head->next;
        free(temp);
        b.num--;
    }
    // comparing the lengthss of the linked lists(bigint numbers)
    if (a.num > b.num)
        return 1;
    else if (a.num < b.num)
        return -1;

    struct Node *p1 = a.head;
    struct Node *p2 = b.head;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->digit > p2->digit)
            return 1; // Magnitude of a is greater

        if (p1->digit < p2->digit)
            return -1; // Magnitude of b is greater

        p1 = p1->next;
        p2 = p2->next;
    }

    return 0; // Both numbers are equal in magnitude
}

// function to find quotient
struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger quo;
    quo.head = NULL;
    quo.num = 0;
    quo.sign = (a.sign * b.sign);

    struct BigInteger temp;
    temp.head = (Node *)malloc(sizeof(Node));
    temp.head->digit = 1;
    temp.head->next = NULL;
    temp.num = 1;
    temp.sign = 1;

    struct BigInteger c;
    c.head = a.head;
    c.num = a.num;
    c.sign = 1;

    struct BigInteger rem;
    rem.head = (Node *)malloc(sizeof(Node));
    rem.head->digit = 0;
    rem.head->next = NULL;
    rem.num = 1;
    rem.sign = 1;

    while (compare(c, b) >= 0)
    {
        struct BigInteger itr;
        itr.head = (Node *)malloc(sizeof(Node));
        itr.head->digit = 0;
        itr.head->next = NULL;
        itr.num = 1;
        itr.sign = 1;

        while (compare(c, b) >= 0)
        {
            c = sub(c, b);
            itr = add(itr, temp);
        }

        quo = add(quo, itr);

        if (c.num == 1 && c.head->digit == 0)
        {
            break;
        }

        struct BigInteger d = mul(b, itr);

        rem = sub(c, d);
    }

    free(temp.head);
    free(rem.head);

    return quo;
}

// finds modulus of the two numbers->remainder
struct BigInteger mod(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger temp = div1(a, b);
    struct BigInteger pro = mul(temp, b);
    struct BigInteger rem = sub(a, pro);

    return rem;
}
