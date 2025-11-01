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

HashMap *hashMapCreate(int sizeKey, void *(*copyKey)(void *), void (*freeKey)(void *), int sizeValue, void *(*copyValue)(void *), void (*freeValue)(void *), uint64_t (*hash)(void *, int), bool (*equals)(void *, void *, int))
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
        SinglyLinkedList *linkedList = singlyLinkedListCreate(sizeof(HashMapNode), &hashMapNodeCopy, &hashMapNodeFree);

        if (linkedList == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCreate \n");
        }

        listAdd(pList, linkedList);
        singlyLinkedListFree(linkedList);
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

void *hashMapGet(HashMap *pMap, void *key)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapGet \n");
        return NULL;
    }
    if (key == NULL)
    {
        printf("[ERROR] : key is null | hashMapGet \n");
        return NULL;
    }

    uint64_t hashCode = hashAdv(pMap, key, pMap->sizeKey);
    int hashValue = hashCode % pMap->length;

    SinglyLinkedList *pList = (SinglyLinkedList *)listGet(pMap->list, hashValue);
    SinglyLinkedListNode *pNode = singlyLinkedListGetHead(pList);

    if (pNode != NULL)
    {
        do
        {
            HashMapNode *temp = (HashMapNode *)singlyLinkedListNodeGet(pList, pNode);
            if (equalsAdv(pMap, key, temp->key, pMap->sizeKey))
            {
                void *value = hashMapNodeGetValue(pMap, temp);

                hashMapNodeFree(temp);
                singlyLinkedListFree(pList);

                return value;
            }

            hashMapNodeFree(temp);
        } while ((pNode = singlyLinkedListNodeNext(pNode)) != NULL);
    }
    singlyLinkedListFree(pList);

    return NULL;
}

int hashMapSet(HashMap *pMap, void *value, void *key)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapSet \n");
        return -1;
    }
    if (value == NULL)
    {
        printf("[ERROR] : value is NULL | hashMapSet \n");
        return -1;
    }
    if (key == NULL)
    {
        printf("[ERROR] : key is null | hashMapSet \n");
        return -1;
    }

    uint64_t hashCode = hashAdv(pMap, key, pMap->sizeKey);
    int hashValue = hashCode % pMap->length;

    HashMapNode *newNode = hashMapCreateNode(pMap, key, value, hashCode);

    SinglyLinkedList *pList = (SinglyLinkedList *)listGet(pMap->list, hashValue);
    SinglyLinkedListNode *pNode = singlyLinkedListGetHead(pList);

    if (pNode != NULL)
    {
        do
        {
            HashMapNode *temp = (HashMapNode *)singlyLinkedListNodeGet(pList, pNode);
            if (equalsAdv(pMap, key, temp->key, pMap->sizeKey))
            {
                int st1 = singlyLinkedListNodeSet(pList, pNode, newNode);

                if (st1 == -1)
                {
                    printf("[ERROR] : function singlyLinkedListNodeSet failed | hashMapSet \n");
                    return -1;
                }

                listSet(pMap->list, pList, hashValue);

                hashMapNodeFree(temp);
                hashMapNodeFree(newNode);
                singlyLinkedListFree(pList);

                return 0;
            }

            hashMapNodeFree(temp);
        } while ((pNode = singlyLinkedListNodeNext(pNode)) != NULL);
    }
    singlyLinkedListFree(pList);
    hashMapNodeFree(newNode);

    return -1;
}

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

List *hashMapToList(HashMap *pMap)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapToList \n");
        return NULL;
    }

    List *pList = listCreate(sizeof(HashMapNode), &hashMapNodeCopy, &hashMapNodeFree);

    if (pList == NULL)
    {
        printf("[ERROR] : Memory allocation failed | hashMapToList \n");
        return NULL;
    }

    for (int i = 0; i < pMap->length; i++)
    {
        SinglyLinkedList *tempList = (SinglyLinkedList *)listGet(pMap->list, i);
        SinglyLinkedListNode *pNode = singlyLinkedListGetHead(tempList);

        for (int j = 0; j < singlyLinkedListLength(tempList); j++)
        {
            HashMapNode *tempNode = (HashMapNode *)singlyLinkedListNodeGet(tempList, pNode);
            listAdd(pList, tempNode);
            hashMapNodeFree(tempNode);
            pNode = singlyLinkedListNodeNext(pNode);
        }

        singlyLinkedListFree(tempList);
    }

    return pList;
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

void *hashMapNodeGetKey(HashMap *pMap, HashMapNode *pNode)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapNodeGetKey \n");
        return NULL;
    }

    if (pNode == NULL)
    {
        printf("[ERROR] : pNode is null | hashMapNodeGetKey \n");
        return NULL;
    }

    void *cp;

    if (pMap->copyKey == NULL)
    {

        cp = (void *)malloc(pMap->sizeKey);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapNodeGetKey \n");
            return NULL;
        }

        memcpy(cp, pNode->key, pMap->sizeKey);
    }
    else
    {
        cp = pMap->copyKey(pNode->key);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapNodeGetKey \n");
            return NULL;
        }
    }

    return cp;
}

void *hashMapNodeGetValue(HashMap *pMap, HashMapNode *pNode)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashMapNodeGetValue \n");
        return NULL;
    }

    if (pNode == NULL)
    {
        printf("[ERROR] : pNode is null | hashMapNodeGetValue \n");
        return NULL;
    }

    void *cp;

    if (pMap->copyValue == NULL)
    {

        cp = (void *)malloc(pMap->sizeValue);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapNodeGetValue \n");
            return NULL;
        }

        memcpy(cp, pNode->value, pMap->sizeValue);
    }
    else
    {
        cp = pMap->copyValue(pNode->value);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapNodeGetValue \n");
            return NULL;
        }
    }

    return cp;
}

uint64_t hashMapNodeGetHash(HashMapNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[ERROR] : pNode is null | hashMapNodeGetHash \n");
        return -1;
    }

    return pNode->hash;
}

uint64_t hashAdv(HashMap *pMap, void *value, int size)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | hashAdv \n");
        return -1;
    }
    if (value == NULL)
    {
        printf("[ERROR] : value is null | hashAdv \n");
        return -1;
    }

    if (pMap->hash == NULL)
    {
        return hash(value, size);
    }
    else
    {
        return pMap->hash(value, size);
    }
}

int simpleInsert(HashMap *pMap, int hashValue, HashMapNode *newNode)
{
    SinglyLinkedList *pList = (SinglyLinkedList *)listGet(pMap->list, hashValue);
    SinglyLinkedListNode *pNode = singlyLinkedListGetHead(pList);

    if (pNode == NULL)
    {
        int st1 = singlyLinkedListAdd(pList, newNode);

        if (st1 == -1)
        {
            printf("[ERROR] : funciont singlyLinkedListAdd failed | hashMapAdd \n");
            return -1;
        }
    }
    else
    {
        do
        {
            HashMapNode *temp = (HashMapNode *)singlyLinkedListNodeGet(pList, pNode);
            if (equalsAdv(pMap, newNode->key, temp->key, pMap->sizeKey))
            {
                printf("[WARN] : Duplicates are not allowed | hashMapAdd \n");
                hashMapNodeFree(temp);
                hashMapNodeFree(newNode);
                singlyLinkedListFree(pList);
                return -1;
            }

            hashMapNodeFree(temp);

        } while ((pNode = singlyLinkedListNodeNext(pNode)) != NULL);

        singlyLinkedListAdd(pList, newNode);
    }

    listSet(pMap->list, pList, hashValue);
    singlyLinkedListFree(pList);

    return 0;
}

bool equalsAdv(HashMap *pMap, void *value1, void *value2, int size)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | equalsAdv \n");
        return NULL;
    }

    if (value1 == NULL || value2 == NULL)
    {
        printf("[ERROR] : value is null | equalsAdv \n");
        return false;
    }

    if (pMap->equals == NULL)
    {
        return equals(value1, value2, size);
    }
    else
    {
        return pMap->equals(value1, value2, size);
    }
}

double getLoadFactor(HashMap *pMap)
{
    return (double)pMap->size / (double)pMap->length;
}

int resizeHashMap(HashMap *pMap)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | resizeHashMap \n");
        return -1;
    }

    List *pCopy = hashMapToList(pMap);
    int st1 = clearHashMap(pMap);

    if (st1 == -1)
    {
        printf("[ERROR] : function clearHashMap failed | resizeHashMap \n");
        return -1;
    }

    int newLength = pMap->length * 2;

    List *pList = pMap->list;

    for (int i = pMap->length; i < newLength; i++)
    {

        SinglyLinkedList *linkedList = singlyLinkedListCreate(sizeof(HashMapNode), &hashMapNodeCopy, &hashMapNodeFree);

        if (linkedList == NULL)
        {
            printf("[ERROR] : Memory allocation failed | resizeHashMap \n");
            return -1;
        }

        listAdd(pList, linkedList);
        singlyLinkedListFree(linkedList);
    }

    pMap->length = newLength;
    pMap->size = listLength(pCopy);

    for (int i = 0; i < listLength(pCopy); i++)
    {
        HashMapNode *tempNode = listGet(pCopy, i);

        int hashValue = tempNode->hash % pMap->length;

        int st2 = simpleInsert(pMap, hashValue, tempNode);
        hashMapNodeFree(tempNode);

        if (st2 == -1)
        {
            printf("[ERROR] : Function simpleInsert failed | resizeHashMap \n");
            return -1;
        }
    }

    listFree(pCopy);

    return 0;
}

int clearHashMap(HashMap *pMap)
{
    if (pMap == NULL)
    {
        printf("[ERROR] : pMap is null | clearHashMap \n");
        return -1;
    }

    int length = pMap->size;

    List *pList = pMap->list;

    for (int i = 0; i < length; i++)
    {
        SinglyLinkedList *linkedList = (SinglyLinkedList *)listGet(pList, i);
        SinglyLinkedListNode *pNode = singlyLinkedListGetHead(linkedList);

        if (pNode == NULL)
        {
            singlyLinkedListFree(linkedList);
            continue;
        }

        int lengthList = singlyLinkedListLength(linkedList);

        for (int j = 0; j < lengthList; j++)
        {
            singlyLinkedListRemove(linkedList, 0);
        }

        listSet(pList, linkedList, i);
        singlyLinkedListFree(linkedList);
    }
    pMap->size = 0;

    return 0;
}

HashMapNode *hashMapCreateNode(HashMap *pMap, void *key, void *value, uint64_t hash)
{
    if (key == NULL)
    {
        printf("[ERROR] : key is null | hashMapCreateNode \n");
        return NULL;
    }

    if (value == NULL)
    {
        printf("[ERROR] : value is null | hashMapCreateNode \n");
        return NULL;
    }

    HashMapNode *pNode = (HashMapNode *)malloc(sizeof(HashMapNode));

    if (pNode == NULL)
    {
        printf("[ERROR] : Memory allocation failed | hashMapCreateNode \n");
        return NULL;
    }

    void *cK;
    void *cV;

    if (pMap->copyKey == NULL)
    {
        cK = (void *)malloc(pMap->sizeKey);

        if (cK == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCreateNode \n");
            return NULL;
        }

        memcpy(cK, key, pMap->sizeKey);
    }
    else
    {
        cK = pMap->copyKey(key);

        if (cK == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCreateNode \n");
            return NULL;
        }
    }

    if (pMap->copyValue == NULL)
    {
        cV = (void *)malloc(pMap->sizeValue);

        if (cV == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCreateNode \n");
            return NULL;
        }

        memcpy(cV, value, pMap->sizeValue);
    }
    else
    {
        cV = pMap->copyValue(value);

        if (cV == NULL)
        {
            printf("[ERROR] : Memory allocation failed | hashMapCreateNode \n");
            return NULL;
        }
    }

    pNode->key = cK;
    pNode->value = cV;
    pNode->hash = hash;
    pNode->sizeKey = pMap->sizeKey;
    pNode->sizeValue = pMap->sizeValue;
    pNode->copyKey = pMap->copyKey;
    pNode->freeKey = pMap->freeKey;
    pNode->copyValue = pMap->copyValue;
    pNode->freeValue = pMap->freeValue;

    return pNode;
}

uint64_t hash(void *value, int size)
{
    if (value == NULL)
    {
        printf("[ERROR] : value is null | hash \n");
        return -1;
    }

    uint64_t initialHash = 4366080005767977372;

    int iterations = (size / 8) + 1;
    int pos = 0;
    int8_t *pValue = (int8_t *)value;

    for (int i = 0; i < iterations && i < 16; i++)
    {
        int chunkSize = 8;
        if (size - pos < 8)
        {
            chunkSize = size - pos;
        }

        uint64_t chunkValue = 0;

        for (int j = 0; j < chunkSize; j++)
        {
            chunkValue |= ((uint64_t)pValue[pos + j]) << (8 * j);
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

    if (memcmp(value1, value2, size) == 0)
    {
        return true;
    }
    return false;
}

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

void hashMapNodeFree(void *pNode)
{
    HashMapNode *pN = (HashMapNode *)pNode;
    if (pN == NULL)
    {
        printf("[ERROR] : pNode is null | hashMapNodeCopy \n");
        return;
    }

    if (pN->freeKey == NULL)
    {
        free(pN->key);
    }
    else
    {
        pN->freeKey(pN->key);
    }
    if (pN->freeValue == NULL)
    {
        free(pN->freeValue);
    }
    else
    {
        pN->freeValue(pN->value);
    }

    pN->key = NULL;
    pN->value = NULL;

    free(pN);

    pN = NULL;
}
