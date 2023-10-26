#ifndef BigInteger_h
#define BigInteger_h

typedef struct Node
{
    int digit;
    struct Node *next;
} Node;

struct BigInteger
{
    Node *head;
    int num;
    int sign;
};

struct BigInteger initialize(char *s);
void addDigit(struct BigInteger *n, int val);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
struct BigInteger mod(struct BigInteger a, struct BigInteger b);
void display(struct BigInteger n);

#endif
