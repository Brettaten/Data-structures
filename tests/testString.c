#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

char *add(char *pList);

int main()
{
    char *pString = stringCreate(NULL);
    pString = add(pString);
    pString = stringAddIndex(pString, 65, 1);
    pString = stringRemove(pString, 2);

    char *pString2 = stringCreate(NULL);
    strcpy(pString2, pString);
    bool equals = strcmp(pString, pString2) == 0;

    pString2 = strcat(pString2, pString);
    pString2[5] = 65;
    stringSwap(pString2, 4, 7);

    char *pString3 = stringSub(pString, 4, 8);

    char *pString4 = stringCreate("A");
    char *pString5 = stringCreate("AB");
    pString = stringReplace(pString, pString4, pString5);
    pString = stringReplace(pString, pString5, pString4);

    bool equals2 = strcmp(pString, pString2) == 0;

    pString4 = stringClear(pString4);
    pString5 = stringClear(pString5);

    printf("%s\n", pString);
    printf("%s\n", pString2);
    printf("%s\n", pString3);
    printf("%s\n", pString4);
    printf("%s\n", pString5);

    return 0;
}

char *add(char *pList)
{
    for (int i = 65; i < 80; i++)
    {
        pList = stringAdd(pList, i);
    }
    return pList;
}
