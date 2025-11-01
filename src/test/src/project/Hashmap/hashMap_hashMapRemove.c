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










int hashMapRemove(HashMap *pMap, void *key)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapRemove \n");
        return -1;
    }
    if (key == NULL)
    {
        printf("[ERROR] : key is null | hashMapRemove \n");
        return -1;
    }

    uint64_t hashCode = hashAdv(pMap, key, pMap->sizeKey);
    int hashValue = hashCode % pMap->length;

    SinglyLinkedList *pList = (SinglyLinkedList *)listGet(pMap->list, hashValue);
    SinglyLinkedListNode *pNode = singlyLinkedListGetHead(pList);

    int counter = 0;

    if (pNode != NULL)
    {
        do
        {
            HashMapNode *temp = (HashMapNode *)singlyLinkedListNodeGet(pList, pNode);
            if (equalsAdv(pMap, key, temp->key, pMap->sizeKey))
            {
                int st1 = singlyLinkedListRemove(pList, counter);

                if (st1 == -1)
                {
                    printf("[ERROR] : function singlyLinkedListRemove failed | hashMapRemove \n");
                    return -1;
                }

                pMap->size--;
                listSet(pMap->list, pList, hashValue);

                hashMapNodeFree(temp);
                singlyLinkedListFree(pList);

                return 0;
            }

            hashMapNodeFree(temp);
            counter++;
        } while ((pNode = singlyLinkedListNodeNext(pNode)) != NULL);
    }
    singlyLinkedListFree(pList);

    return -1;
}
