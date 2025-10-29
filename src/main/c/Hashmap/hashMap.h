#include <stdint.h>
#include <stdbool.h>

#include "../List/list.h"

/**
 * Struct that represents a hash map
 *
 * @note Only use this hash map to store data that has the same size as specified.
 * @note Only store one data type in each hash map to be safe.
 */
typedef struct HashMap HashMap;

/**
 * Struct that represents an entry of a hashmap
 */
typedef struct HashMapNode HashMapNode;

/**
 * Function that allocates memory for a hash map struct
 *
 * @param sizeKey the size of the keys that will be stored in the hash map
 * @param copyKey pointer to a function that deep copies the key, pass NULL for elements, where a shallow copy is sufficient
 * @param freeKey pointer to a function that deep frees the key, pass NULL for elements, where a shallow free is sufficient
 * @param sizeValue the size of the values that will be stored in the hash map
 * @param copyValue pointer to a function that deep copies the value, pass NULL for elements, where a shallow copy is sufficient
 * @param freeValue pointer to a function that deep frees the value, pass NULL for elements, where a shallow free is sufficient
 * @param hash Pointer to a function that hashes the key, pass NULL for keys, where a shallow hash is sufficient
 * @param equals Pointer to a function that compares the keys, pass NULL for keys, where a shallow compare is sufficient
 *
 * @return Success: Pointer to the created hash map | Failure: NULL
 */
HashMap *hashMapCreate(int sizeKey, void *(*copyKey)(void *), void (*freeKey)(void *), int sizeValue, void *(*copyValue)(void *), void (*freeValue)(void *), int64_t (*hash)(void *, int), bool (*equals)(void *, void *, int));

/**
 * Function that retrieves the element of the hash map with the passed key
 *
 * @param pMap pointer to the hash map
 * @param key the key
 *
 * @return Success: Pointer to the element of the passed key | Failure: NULL
 *
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *hashMapGet(HashMap *pMap, void *key);

/**
 * Function that sets the value of the element that is associated with the passed key
 *
 * @param pMap pointer to the hash map
 * @param value pointer to the element that should replace the old element
 * @param index the key
 *
 * @return Success: 0 | Failure: -1
 *
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the hash map.
 */
int hashMapSet(HashMap *pMap, void *value, void *key);

/**
 * Function used to add the passed value to the hash map
 *
 * @param pMap pointer to the hash map
 * @param value pointer to a value
 * @param key the key
 *
 * @return Success: 0 | Failure: -1
 *
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the hash map.
 */
int hashMapAdd(HashMap *pMap, void *value, void *key);

/**
 * Function used to remove the data that is associated with the passed key
 *
 * @param pMap pointer to the hash map
 * @param key the key
 *
 * @return Success: 0 | Failure: -1
 */
int hashMapRemove(HashMap *pMap, void *key);

/**
 * Function used to transform the passed hash map to a list
 * 
 * @param pMap the pointer to the hash map
 * 
 * @return Success: pointer to a list | Failure: NULL
 */
List *hashMapToList(HashMap *pMap);

/**
 * Function used to return the length of the hash map
 *
 * @param pMap pointer to the hash map
 *
 * @return Success: length | Failure: -1
 */
int hashMapLength(HashMap *pMap);

/**
 * Function used to return the size of the key
 *
 * @param pMap pointer to the hash map
 *
 * @return Success: size | Failure: -1
 */
int hashMapKeySize(HashMap *pMap);

/**
 * Function used to return the size of the value
 *
 * @param pMap pointer to the hash map
 *
 * @return Success: size | Failure: -1
 */
int hashMapValueSize(HashMap *pMap);

/**
 * Function used to return the size of a hash map struct
 *
 * @return Success: size
 */
int hashMapSize();

/**
 * Function used to create a deep copy of a hash map
 *
 * @param pMap the pointer to the hash map
 *
 * @return Success: the copy of the hash map | Failure: NULL
 *
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void *hashMapCopy(void *pMap);

/**
 * Function used to free the passed hash map
 *
 * @param pList pointer to the hash map
 * 
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void hashMapFree(void *pMap);

/**
 * Function used to retrieve the key of a hash map node
 * 
 * @param pMap pointer to the hash map
 * @param pNode pointer to the node
 * 
 * @return Success: pointer to the key | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *hashMapNodeGetKey(HashMap *pMap, HashMapNode *pNode);

/**
 * Function used to retrieve the value of a hash map node
 * 
 * @param pMap pointer to the hash map
 * @param pNode pointer to the node
 * 
 * @return Success: pointer to the value | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *hashMapNodeGetValue(HashMap *pMap, HashMapNode *pNode);

/**
 * Function used to retrieve the hash of a hash map node
 * 
 * @param pNode pointer to the node
 * 
 * @return Success: hash | Failure: -1
 */
int64_t hashMapNodeGetHash(HashMapNode *pNode);

/**
 * Funcion used to create a deep copy of the passed HashMapNode
 *
 * @param pNode the pointer to the node
 *
 * @return Success: the deep copy | Failure: NULL
 */
void *hashMapNodeCopy(void *pNode);

/**
 * Function used to free the passed HashMapNode
 *
 * @param pNode the pointer to the node
 */
void hashMapNodeFree(void *pNode);