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






void addBig(HashMap *pMap, char *cp)
{
    for (int i = 0; i < 20; i++)
    {
        BigObj *big = (BigObj *)malloc(sizeof(BigObj));
        big->id = i;
        big->str = cp;

        hashMapAdd(pMap, big, big);
    }
}
