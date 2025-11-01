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










void freeBig(void *big)
{
    BigObj *pBig = (BigObj *)big;

    free(pBig->str);
    free(pBig);
}
