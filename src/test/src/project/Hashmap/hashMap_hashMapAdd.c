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








int hashMapAdd(HashMap *pMap, void *value, void *key)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapAdd \n");
        return -1;
    }
    if (value == NULL)
    {
        printf("[ERROR] : value is NULL | hashMapAdd \n");
        return -1;
    }
    if (key == NULL)
    {
        printf("[ERROR] : key is null | hashMapAdd \n");
        return -1;
    }

    uint64_t hashCode = hashAdv(pMap, key, pMap->sizeKey);
    int hashValue = hashCode % pMap->length;

    HashMapNode *newNode = hashMapCreateNode(pMap, key, value, hashCode);

    int st1 = simpleInsert(pMap, hashValue, newNode);
    hashMapNodeFree(newNode);

    if (st1 == -1)
    {
        printf("[ERROR] : Function simpleInsert failed | hashMapAdd \n");
        return -1;
    }

    pMap->size++;

    double loadFactor = getLoadFactor(pMap);

    if (loadFactor >= 1.0)
    {
        int st2 = resizeHashMap(pMap);

        if (st2 == -1)
        {
            printf("[ERROR] : function resizeHashMap failed | hashMapAdd \n");
            return -1;
        }
    }

    return 0;
}
