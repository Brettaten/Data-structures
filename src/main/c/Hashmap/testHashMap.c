#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashMap.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;

// void add(BinarySearchTree *pBinarySearchTree);
// void addBig(BinarySearchTree *pBinarySearchTree, char *cp);
// void *copyBig(void *big);
// void freeBig(void *big);

int main()
{


}

// void add(BinarySearchTree *pBinarySearchTree)
// {
//     for (int i = 0; i < 15; i++)
//     {
//         binarySearchTreeInsert(pBinarySearchTree, &i, i);
//         printf("%s\n", isRedBlackTree(pBinarySearchTree) ? "true" : "false");
//     }
// }

// void addBig(BinarySearchTree *pBinarySearchTree, char *cp)
// {
//     for (int i = 0; i < 15; i++)
//     {
//         BigObj *big = (BigObj *)malloc(sizeof(BigObj));
//         big->id = i;
//         big->str = cp;

//         binarySearchTreeInsert(pBinarySearchTree, big, i);
//         printf("%s\n", isRedBlackTree(pBinarySearchTree) ? "true" : "false");
//     }
// }

// void *copyBig(void *big)
// {
//     BigObj *pBig = (BigObj *)big;

//     char *cp = (char *)malloc(sizeof(char) * (pBig->id + 1));

//     if (cp == NULL)
//     {
//         printf("LOL");
//     }

//     memcpy(cp, pBig->str, sizeof(char) * (pBig->id + 1));

//     BigObj *cpp = (BigObj *)malloc(sizeof(BigObj));

//     memcpy(cpp, pBig, sizeof(BigObj));

//     cpp->id = pBig->id;
//     cpp->str = cp;

//     return cpp;
// }

// void freeBig(void *big)
// {
//     BigObj *pBig = (BigObj *)big;

//     free(pBig->str);
//     free(pBig);
// }
