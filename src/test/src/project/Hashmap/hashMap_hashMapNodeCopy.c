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
    uint64_t (*hash)(void *, int);
    bool (*equals)(void *, void *, int);
} HashMap;


typedef struct HashMapNode
{
    void *key;
    void *value;
    uint64_t hash;
    int sizeKey;
    int sizeValue;
    void *(*copyKey)(void *);
    void (*freeKey)(void *);
    void *(*copyValue)(void *);
    void (*freeValue)(void *);
} HashMapNode;


/**
 * Function used to hash any pointer to a 64 bit integer
 *
 * @param pMap pointer to the hash map
 * @param value pointer to the value
 * @param size the size that value holds
 *
 * @return Success: a 64 bit hash | Failure: NULL
 */

uint64_t hashAdv(HashMap *pMap, void *value, int size);


/**
 * Function used to insert one node into the hash map
 *
 * @param pMap pointer to the hash map
 * @param hashValue the index
 * @param newNode the node that should be inserted
 *
 * @return Success: 0 | Failure: -1
 */

int simpleInsert(HashMap *pMap, int hashValue, HashMapNode *newNode);


/**
 * Function used to test if two variables store the same bits
 *
 * @param pMap pointer to the hash map
 * @param value1 pointer to the first value
 * @param value2 pointer to the second value
 * @param size the size of both pointers
 *
 * @return Success: true | Failure: false
 */

bool equalsAdv(HashMap *pMap, void *value1, void *value2, int size);


/**
 * Function used to retrieve the load factor of the passed hash map
 *
 * @param pMap pointer to the hash map
 */

double getLoadFactor(HashMap *pMap);


/**
 * Function used to resize a hash map
 *
 * @param pMap the pointer to the hash map
 *
 * @return Success: 0 | Failure: -1
 */

int resizeHashMap(HashMap *pMap);


/**
 * Function used to clear all HashMapNodes of the passed map
 *
 * @param pMap the pointer to the hash map
 *
 * @return Success: 0 | Failure: 0
 */

int clearHashMap(HashMap *pMap);


/**
 * Function used to create a hash map node
 *
 * @param pMap pointer to the map
 * @param key pointer to the key
 * @param value pointer to the value
 * @param hash the hash
 *
 * @return Success: pointer to a node | Failure: NULL
 */

HashMapNode *hashMapCreateNode(HashMap *pMap, void *key, void *value, uint64_t hash);


















































void *hashMapNodeCopy(void *pNode)
{
    HashMapNode *pN = (HashMapNode *)pNode;
    if (pN == NULL)
    {
        printf("[ERROR] : pNode is null | hashMapNodeCopy \n");
        return NULL;
    }

    HashMapNode *cp = (HashMapNode *)malloc(sizeof(HashMapNode));

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | hashMapNodeCopy \n");
        return NULL;
    }

    void *cK;
    void *cV;

    if (pN->copyKey == NULL)
    {
        cK = (void *)malloc(pN->sizeKey);

        if (cK == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapNodeCopy \n");
            return NULL;
        }

        memcpy(cK, pN->key, pN->sizeKey);
    }
    else
    {
        cK = pN->copyKey(pN->key);

        if (cK == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapNodeCopy \n");
            return NULL;
        }
    }

    if (pN->copyValue == NULL)
    {
        cV = (void *)malloc(pN->sizeValue);

        if (cV == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapNodeCopy \n");
            return NULL;
        }

        memcpy(cV, pN->value, pN->sizeValue);
    }
    else
    {
        cV = pN->copyValue(pN->value);

        if (cV == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapNodeCopy \n");
            return NULL;
        }
    }

    cp->key = cK;
    cp->value = cV;
    cp->hash = pN->hash;
    cp->sizeKey = pN->sizeKey;
    cp->sizeValue = pN->sizeValue;
    cp->copyKey = pN->copyKey;
    cp->freeKey = pN->freeKey;
    cp->copyValue = pN->copyValue;
    cp->freeValue = pN->freeValue;

    return cp;
}
