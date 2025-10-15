#include "testInsert.h"
#include "../util/cbuilderTest.h"
#include "../../../../../main/c/BinarySearchTree/binarySearchTree.h"

bool called = false;
int freed = 0;
int copied = 0;

void testbinarySearchTreeInsertRoot()
{
    BinarySearchTree *pTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    int value = 10;

    binarySearchTreeInsert(pTree, &value, 1);

    assert(called == false);
}

void testbinarySearchTreeInsert()
{
    BinarySearchTree *pTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    int value = 10;
    binarySearchTreeInsert(pTree, &value, 1);

    int value2 = 10;
    binarySearchTreeInsert(pTree, &value2, 2);

    int value3 = 10;
    binarySearchTreeInsert(pTree, &value3, 3);

    assert(called == true);
}

void testbinarySearchTreeFree()
{
    BinarySearchTree *pTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    int value = 10;
    binarySearchTreeInsert(pTree, &value, 1);

    int value2 = 10;
    binarySearchTreeInsert(pTree, &value2, 2);

    int value3 = 10;
    binarySearchTreeInsert(pTree, &value3, 3);

    int value4 = 10;
    binarySearchTreeInsert(pTree, &value4, 4);

    binarySearchTreeFree(pTree);

    assert(freed == 4);
}

void testbinarySearchTreeCopy()
{
    BinarySearchTree *pTree = binarySearchTreeCreate(sizeof(int), NULL, NULL);

    int value = 10;
    binarySearchTreeInsert(pTree, &value, 1);

    int value2 = 10;
    binarySearchTreeInsert(pTree, &value2, 2);

    int value3 = 10;
    binarySearchTreeInsert(pTree, &value3, 3);

    int value4 = 10;
    binarySearchTreeInsert(pTree, &value4, 4);

    binarySearchTreeCopy(pTree);

    assert(copied == 4);
}

void fixInsert(BinarySearchTree *pTree, BinarySearchTreeNode *pNode)
{
    called = true;
}

void binarySearchTreeFreeNode(BinarySearchTreeNode *pNode)
{
    freed++;
}

void *binarySearchTreeCopyNode(void *pTree)
{
    copied++;
    return pTree;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "C:/Users/richt/Programmieren/C/Datastructures/src/test/src/main/genTests/util/cbuilderTest.h"
int main(int argc, char *argv[]){
	int64_t before, after, time;
	strcpy(path,"C:/Users/richt/Programmieren/C/Datastructures/src/test/src/main/genTests/util/temp.txt");
	bool isEnd = false;
	if(argc == 2){
		int end = atoi(argv[1]);
		if(end == 1){
			isEnd = true;
		}
	}
	getStats();
	passed = true;
	printf("TEST 1 | testbinarySearchTreeInsertRoot\n");
	before = getTime();
	testbinarySearchTreeInsertRoot();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	passed = true;
	printf("TEST 2 | testbinarySearchTreeInsert\n");
	before = getTime();
	testbinarySearchTreeInsert();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	passed = true;
	printf("TEST 3 | testbinarySearchTreeFree\n");
	before = getTime();
	testbinarySearchTreeFree();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	passed = true;
	printf("TEST 4 | testbinarySearchTreeCopy\n");
	before = getTime();
	testbinarySearchTreeCopy();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	if(isEnd && testExe > 0){
		printf("--------------------------------------------------\n");
		testPassedRel = ((double)testPassed / (double)testExe) * 100.0;
		testFailedRel = ((double)testFailed / (double)testExe) * 100.0;
		printf("Tests executed: %d | Total execution time: %d ms\n",testExe, executionTime);
		printf("Tests passed: %d | %.2f %%\n",testPassed, testPassedRel);
		printf("Tests failed: %d | %.2f %%\n",testFailed, testFailedRel);
		remove(path);
	} else if(isEnd && testExe == 0){
		printf("--------------------------------------------------\n");
		printf("No test was executed");
	}
	else{
		saveStats();
	}
}