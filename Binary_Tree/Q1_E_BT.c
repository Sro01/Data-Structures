//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int identical(BTNode *tree1, BTNode *tree2);

BTNode* createBTNode(int item);

BTNode* createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("Please input your choice(1/2/3/0): ");
        if(scanf("%d", &c) > 0)

        {

            switch(c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if(s){
                printf("Both trees are structurally identical.\n");
                }
                else{
                printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int identical(BTNode *tree1, BTNode *tree2) {
    Stack stk1;
    Stack stk2;
    BTNode *temp1;
    BTNode *temp2;
    stk1.top = NULL;
    stk2.top = NULL;

    if (tree1 == NULL && tree2 == NULL) return 1;
    if (tree1 == NULL || tree2 == NULL) return 0;

    // 루트부터 순회
    push(&stk1, tree1);
    push(&stk2, tree2);

    // 스택 둘 중 하나라도 top이 NULL이 아니면 계속 실행 (둘 다 top이 NULL이어야 종료)
    while(stk1.top != NULL || stk2.top != NULL) {
        if (stk1.top == NULL || stk2.top == NULL) return 0;

        temp1 = pop(&stk1);
        temp2 = pop(&stk2);

        // 두 tree의 item이 다르면 종료
        if (temp1->item != temp2->item) return 0;
        
        // 두 tree의 item이 같으면
        else {
            // 둘 다 NULL이거나 둘 다 NULL이 아니어야 함 (둘 중 하나라도 left가 NULL이면 다른 구조의 트리)            
            if (temp1->left != NULL && temp2->left != NULL) {
                // 각 트리의 left를 스택에 push
                push(&stk1,temp1->left);
                push(&stk2,temp2->left);
            } else if (temp1->left == NULL && temp2->left == NULL);
            else return 0;

            // 둘 다 right를 가지고 있어야 함
            if (temp1->right != NULL && temp2->right != NULL) {
                // 각 트리의 right를 스택에 push
                push(&stk1,temp1->right);
                push(&stk2,temp2->right);
            } else if (temp1->right == NULL && temp2->right == NULL);
            else return 0;
        }
    }

    return 1;
}

/////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()
{
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item); // 트리 루트 노드 생성
        push(&stk,root); // 루트를 스택에 push
    }
    else
    {
        scanf("%c",&s); // 숫자값이 아니라면 스택에 push 하지 않음
    }

    while((temp=pop(&stk)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item) > 0) // 숫자값을 입력 받으면
        {
            temp->left = createBTNode(item); // 왼쪽 노드 생성, left 포인터 초기화
        }
        else
        {
            scanf("%c",&s); // 숫자가 아니면 그대로 temp->left는 NULL을 가리킴
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item) > 0)
        {
            temp->right = createBTNode(item); // 오른쪽 노드 생성, right 포인터 초기화
        }
        else
        {
            scanf("%c",&s); // 숫자가 아니면 그대로 temp->right NULL을 가리킴
        }

        // 왼쪽 노드를 먼저 입력 받기 때문에 오른쪽 노드부터 push해야 왼쪽 노드 먼저 pop됨
        if(temp->right != NULL)
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

void push(Stack *stk, BTNode *node) {
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stk->top == NULL){
        stk->top = temp;
        temp->next = NULL;
    }
    else{
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode* pop(Stack *stk){
   StackNode *temp, *top;
   BTNode *ptr;
   ptr = NULL;

   top = stk->top;
   if(top != NULL){
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
   }
   return ptr;
}

void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
