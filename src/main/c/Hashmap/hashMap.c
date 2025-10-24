#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hashMap.h"
#include "../List/list.h"
#include "../SinglyLinkedList/singlyLinkedList.h"

typedef struct HashMap
{
    List *list;
    int length;
    int size;
    int sizeKey;
    int sizeValue;
    void *(*copyKey)(void *);
    void (*freeKey)(void *);
    void *(*copyValue)(void *);
    void (*freeValue)(void *);
    int64_t *(*hash)(void *, int);
    bool *(*equals)(void *, void *, int);
} HashMap;

/**
 * Struct that represents an entry of a hashmap
 */
typedef struct Node
{
    void *key;
    void *value;
    int64_t hash;
} Node;

/**
 * Function used to hash any pointer to a 64 bit integer
 *
 * @param value pointer to the value
 * @param size the size that value holds
 *
 * @return Success: a 64 bit hash | Failure: NULL
 */
int64_t hash(void *value, int size);

/**
 * Function used to test if two variables store the same bits
 *
 * @param value1 pointer to the first value
 * @param value2 pointer to the second value
 * @param size the size of both pointers
 *
 * @return Success: true | Failure: false
 */
bool equals(void *value1, void *value2, int size);

/**
 * Funcion used to create a deep copy of the passed Node
 *
 * @param pMap the pointer to the hash map
 * @param pNode the pointer to the node
 *
 * @return Success: the deep copy | Failure: NULL
 */
Node *hashMapCopyNode(HashMap *pMap, Node *pNode);

/**
 * Function used to free the passed Node
 *
 * @param pMap the pointer to the hash map
 * @param pNode the pointer to the node
 */
void hashMapFreeNode(HashMap *pMap, Node *pNode);

HashMap *hashMapCreate(int sizeKey, void *(*copyKey)(void *), void (*freeKey)(void *), int sizeValue, void *(*copyValue)(void *), void (*freeValue)(void *), int64_t *(*hash)(void *, int), bool *(*equals)(void *, void *, int))
{
    HashMap *pMap = (HashMap *)malloc(sizeof(HashMap));

    if (pMap == NULL)
    {
        printf("[ERROR] : Memory allocation failed | hashMapCreate \n");
        return NULL;
    }

    List *pList = listCreate(sizeof(singlyLinkedListSize()), &singlyLinkedListCopy, &singlyLinkedListFree);

    if (pList == NULL)
    {
        printf("[ERROR] : Memory allocation failed | hashmapCreate \n");
        return NULL;
    }

    int initalSize = 16;

    for (int i = 0; i < initalSize; i++)
    {
        SinglyLinkedList *linkedList = singlyLinkedListCreate(sizeof(Node), &hashMapCopyNode, &hashMapFreeNode);

        if (linkedList == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCreate \n");
        }

        listAdd(pList, linkedList);
    }

    pMap->list = pList;
    pMap->length = initalSize;
    pMap->size = 0;
    pMap->sizeKey = sizeKey;
    pMap->sizeValue = sizeValue;
    pMap->copyKey = copyKey;
    pMap->freeKey = freeKey;
    pMap->copyValue = copyValue;
    pMap->freeValue = freeValue;
    pMap->hash = hash;
    pMap->equals = equals;

    return pMap;
}

int hashMapLength(HashMap *pMap)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapLength \n");
        return -1;
    }

    return pMap->size;
}

int hashMapKeySize(HashMap *pMap)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapKeySize \n");
        return -1;
    }

    return pMap->sizeKey;
}

int hashMapValueSize(HashMap *pMap)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapValueSize \n");
        return -1;
    }

    return pMap->sizeValue;
}

int hashMapSize()
{
    return sizeof(HashMap);
}

void *hashMapCopy(void *pMap)
{
    HashMap *cp = (HashMap *)pMap;

    if (cp == NULL)
    {
        printf("[ERROR] : HashMap is null | hashMapCopy \n");
        return NULL;
    }

    HashMap *copy = (HashMap *)malloc(sizeof(HashMap));

    if (copy == NULL)
    {
        printf("[ERROR] : Memory allocation failed | hashMapCopy \n");
        return NULL;
    }

    List *pListCopy = listCopy(cp->list);

    if (pListCopy == NULL)
    {
        printf("[ERROR] : Memory allocation failed | hashMapCopy \n");
    }

    copy->list = pListCopy;
    copy->length = cp->length;
    copy->size = cp->size;
    copy->sizeKey = cp->sizeKey;
    copy->sizeValue = cp->sizeValue;
    copy->copyKey = cp->copyKey;
    copy->freeKey = cp->freeKey;
    copy->copyValue = cp->copyValue;
    copy->freeValue = cp->freeValue;
    copy->hash = cp->hash;
    copy->equals = cp->equals;

    return copy;
}

void hashMapFree(void *pMap)
{
    HashMap *cp = (HashMap *)pMap;

    if (cp == NULL)
    {
        printf("[WARN] : Pointer to hash map is NULL | hashMapFree \n");
        return;
    }

    listFree(cp->list);

    free(cp);

    pMap = NULL;
}

int64_t hash(void *value, int size)
{
    if (value == NULL)
    {
        printf("[ERROR] : value is null | hash \n");
        return NULL;
    }

    int64_t initialHash = 4366080005767977372;

    int iterations = (size / 8) + 1;
    int pos = 0;
    int8_t *pValue = (int *)value;

    for (int i = 0; i < iterations && i < 16; i++)
    {
        int chunkSize = 8;
        if (size - pos < 8)
        {
            chunkSize = size - pos;
        }

        int64_t chunkValue = 0;

        for (int j = 0; j < chunkSize; j++)
        {
            chunkValue |= ((int64_t)pValue[pos + j]) << (8 * j);
        }

        initialHash ^= chunkValue;

        pos += chunkSize;

        if (pos >= size)
        {
            break;
        }
    }

    return initialHash;
}

bool equals(void *value1, void *value2, int size)
{
    if (value1 == NULL || value2 == NULL)
    {
        printf("[ERROR] : value is null | equals \n");
        return false;
    }

    if(memcmp(value1, value2, size) == 0){
        return true;
    }
    return false;
}

Node *hashMapCopyNode(HashMap *pMap, Node *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : pNode is null | hashMapCopyNode \n");
        return NULL;
    }

    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapCopyNode \n");
        return NULL;
    }

    Node *cp = (Node *)malloc(sizeof(Node));

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | hashMapCopyNode \n");
        return NULL;
    }

    void *cK;
    void *cV;

    if (pMap->copyKey == NULL)
    {
        cK = (void *)malloc(pMap->sizeKey);

        if (cK == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCopyNode \n");
            return NULL;
        }

        memcpy(cK, pNode->key, pMap->sizeKey);
    }
    else
    {
        cK = pMap->copyKey(pNode->key);

        if (cK == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCopyNode \n");
            return NULL;
        }
    }

    if (pMap->copyValue == NULL)
    {
        cV = (void *)malloc(pMap->sizeValue);

        if (cV == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCopyNode \n");
            return NULL;
        }

        memcpy(cV, pNode->value, pMap->sizeValue);
    }
    else
    {
        cV = pMap->copyValue(pNode->value);

        if (cV == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCopyNode \n");
            return NULL;
        }
    }

    cp->key = cK;
    cp->value = cV;
    cp->hash = pNode->hash;

    return cp;
}

void hashMapFreeNode(HashMap *pMap, Node *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : pNode is null | hashMapCopyNode \n");
        return NULL;
    }

    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapCopyNode \n");
        return NULL;
    }

    if (pMap->freeKey == NULL)
    {
        free(pNode->key);
    }
    else
    {
        pMap->freeKey(pNode->key);
    }
    if (pMap->freeValue == NULL)
    {
        free(pMap->freeValue);
    }
    else
    {
        pMap->freeValue(pNode->value);
    }

    pNode->key = NULL;
    pNode->value = NULL;

    free(pNode);

    pNode = NULL;
}
