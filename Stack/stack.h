typedef struct Stack Stack;

Stack *stackCreate(int size);
int stackPush(Stack *pStack, void *value);
void *stackPop(Stack *pStack);
void *stackPeek(Stack *pStack);
int stackLength(Stack *pStack);
int stackSize(Stack *pStack);
void stackFree(Stack *pStack);
