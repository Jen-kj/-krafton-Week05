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

// Q. 2개의 이진트리 구조, 노드 같은지 판별(동일-> 1, 다름 -> 0)
// 둘 다 빈 트리-> 동일
// 빈 트리X -> 왼쪽, 오른쪽 서브트리 각각 동일 -> 동일

// 구조와 값이 같더라도, 서로 다른 트리면 주소 값이 다름 
// -> '구조+값 동일성' 판단에 포인터 주소로 비교(X) '재귀적으로 값 비교 + 좌/우 재귀 호출' (O)   
//////////////////////////////////////////////////////////////////////////////////

int identical(BTNode *tree1, BTNode *tree2)

{
   if(!tree1 && !tree2) return 1;       // 1. 둘 다 빈 트리 -> 동일
   if (!tree1 || !tree2) return 0;      // 2. 한 쪽만 빈 트리 -> 동일X
   if (tree1->item != tree2->item) return 0;          // 3. 값이 다름 -> 동일X

   return identical(tree1->left, tree2->left) && identical(tree1->right, tree2->right);  // 4. 좌우 서브트리 동일 
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
        root = createBTNode(item);
        push(&stk,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stk)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

void push( Stack *stk, BTNode *node){
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

// 중위순회 출력
void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);       // 1) 왼쪽 서브트리 모두 방문
    printf("%d ",node->item);    // 2) 현재 노드 출력
    printTree(node->right);      // 3) 오른쪽 서브트리 모두 방문
}

// 후위 순회로 돌면서 모든 노드 free
void removeAll(BTNode **node){
    if(*node != NULL){   
        removeAll(&((*node)->left));      // 1) 왼쪽 서브트리부터 모두 해제   
        removeAll(&((*node)->right));     // 2) 오른쪽 서브트리도 모두 해제
        free(*node);                      // 3) 자식 정리 후 현재 노드 해제
        *node = NULL;                     // 4) 호출자 보유 포인터를 NULL로
    }
}
