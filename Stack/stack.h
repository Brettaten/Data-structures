typedef struct Stack Stack;

Stack *stackCreate();
void stackPush(Stack *pStack, void *value);
void *stackPop(Stack *pStack);
int stackLength(Stack *pStack);

void stackFree(Stack *pStack);
