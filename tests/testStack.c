#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;

void add(Stack *pList);
void addBig(Stack *pList, char *cp);
void *copyBig(void *big);
void freeBig(void *big);

int main(){
    Stack *pStack = stackCreate(sizeof(int), NULL, NULL);

    add(pStack);

    int *num = (int *) stackPeek(pStack);
    printf("%d\n", *num);

    int num2 = 99;
    stackPush(pStack, &num2);

    int *num3 = (int *) stackPop(pStack);
    printf("%d\n", *num3);

    int *num4 = (int *) stackPeek(pStack);
    printf("%d\n", *num4);

    Stack *copy = stackCopy(pStack);

    stackFree(pStack);
    
    Stack *pBigStack = stackCreate(sizeof(BigObj), &copyBig, &freeBig);

    char *cp = (char *)malloc(sizeof(char) * (10));
    addBig(pBigStack, cp);

    BigObj *big = (BigObj *) stackPeek(pBigStack);
    printf("%d\n", big->id);

    BigObj *big2 = (BigObj *) malloc(sizeof(BigObj));
    big2->id = 100;
    big2->str = cp;
    stackPush(pBigStack, big2);

    BigObj *big3 = (BigObj *) stackPop(pBigStack);
    printf("%d\n", big3->id);

    BigObj *big4 = (BigObj *) stackPeek(pBigStack);
    printf("%d\n", big4->id);

    free(cp);

    stackFree(pBigStack);

    return 0;
}

void add(Stack *pList){
     for(int i = 0; i < 15; i++){
        stackPush(pList, &i);
    }
}

void addBig(Stack *pStack, char *cp)
{
    for (int i = 0; i < 15; i++)
    {
        BigObj *big = (BigObj *)malloc(sizeof(BigObj));
        big->id = i;
        big->str = cp;

        stackPush(pStack, big);
    }
}

void *copyBig(void *big)
{
    BigObj *pBig = (BigObj *)big;

    char *cp = (char *)malloc(sizeof(char) * (pBig->id + 1));

    if (cp == NULL)
    {
        printf("LOL");
    }

    memcpy(cp, pBig->str, sizeof(char) * (pBig->id + 1));

    BigObj *cpp = (BigObj *)malloc(sizeof(BigObj));

    memcpy(cpp, pBig, sizeof(BigObj));

    cpp->id = pBig->id;
    cpp->str = cp;

    return cpp;
}

void freeBig(void *big)
{
    BigObj *pBig = (BigObj *)big;

    free(pBig->str);
    free(pBig);
}
