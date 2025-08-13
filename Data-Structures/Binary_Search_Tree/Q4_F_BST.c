//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS1(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS1(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}
// Q4. (스택 1개) 후위순회 출력(왼->오->루)

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS1(BSTNode *root)
{
	// 1. 예외 처리: NULL
	if(!root) return;

    // 2. 스택 초기화 + 비우기
    Stack s;
	s.top = NULL;
	while(!isEmpty(&s)) pop(&s);

   // 3. 현재 노드, 방문체크
   BSTNode *cur = root;                 // 지금 내려가고 있는 노드(왼쪽으로 계속 진행)
   BSTNode *lastVisited = NULL;         // 직전에 '방문(출력) 완료'한 노드 저장

   // 4. 후위순회 (왼->오->루)
   while(cur || !isEmpty(&s)) {
	if(cur) {
		push(&s, cur);
		cur = cur->left;       // (1) 왼쪽 끝까지 스택 쌓기(push)

	}else{
		BSTNode *top = peek(&s);    // (2) 더 못 내려가면, 스택의 맨 위 확인(아직 방문 전 조상)

		if(top->right && lastVisited != top->right) {                // (3) 오른쪽 서브트리가 '남아 있고' 아직 방문 전이면, 그쪽으로 이동
			cur = top->right;
		} else{                                                      //(4) 오른쪽도 없거나 이미 방문했다면, 이제 top(현재 노드) '방문'
			BSTNode *node = pop(&s);             // 방금 방문 완료                  
			printf("%d ", node->item); 
			lastVisited = node;                 // 이 노드를 '방문 완료'로 표시
		}
	}
   }
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
