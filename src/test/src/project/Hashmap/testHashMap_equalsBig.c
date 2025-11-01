#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashMap.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;


void add(HashMap *pMap);

void addBig(HashMap *pMap, char *cp);

void *copyBig(void *big);

void freeBig(void *big);

uint64_t hashBig(void *value, int size);

bool equalsBig(void *value1, void *value2, int size);














bool equalsBig(void *big1, void *big2, int size)
{
    BigObj *pBig1 = (BigObj *)big1;
    BigObj *pBig2 = (BigObj *)big2;

    char *str1 = pBig1->str;
    int id1 = pBig1->id;
    char *str2 = pBig2->str;
    int id2 = pBig2->id;

    return equals(str1, str2, sizeof(char)*2) && equals(&id1, &id2, sizeof(int));
}
