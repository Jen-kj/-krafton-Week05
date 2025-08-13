//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Q3. 연결 리스트 내의 홀수 정수들을 모두 뒤로 이동시킴
// 이동 후: 원래 리스트의 순서 유지(짝수끼리, 홀수끼리는 원래 순서 유지)


void moveOddItemsToBack(LinkedList *ll)
{
    // 1. 예외 처리: 리스트가 없거나, 노드 수 0~1이면 작업 불필요
	if(!ll || !ll->head || ll->size <= 1 ) return;

    // 2. 포인터 초기화
	ListNode *evenhead = NULL, *eventail = NULL;    //짝수
	ListNode *oddhead = NULL, *oddtail = NULL;      //홀수

	ListNode *cur = ll->head;
    
	 // 3. 원본 리스트 순회하며 짝수/홀수 체인으로 분리(순서 보존)
	while (cur){
		// 3-1. 다음 노드 백업 + 현재 노드 분리(detach)
		ListNode *next = cur->next;    // 다음 노드 기억
		cur->next = NULL;              // 현재 노드를 독립시켜 재연결 준비
	
        // 3-2. 짝수면 짝수 체인 뒤에 추가
		if ((cur->item & 1) == 0) {
			if (!evenhead) 
				evenhead = eventail = cur;
			else {
				eventail->next = cur;
				eventail = cur;}
		} 
		 // 3-2. 홀수면 홀수 체인 뒤에 추가
		else {
			if (!oddhead) 
				oddhead = oddtail = cur;
			else {
				oddtail->next = cur;
				oddtail = cur;}
			}
            
			// 3-4. 다음 원본 노드로 이동
			cur = next;
		}
        
		// 4. 특수 케이스 처리(전부 홀수 or 전부 짝수)
		if(!evenhead) {ll->head = oddhead; return;}
		if(!oddhead) {ll->head = evenhead; return;}
        
		// 5. 최종 연결(짝수 체인 뒤에 홀수 체인 연결) 및 head 갱신
		eventail->next = oddhead;     // 짝수들(원순서) 뒤에 홀수들(원순서)
		ll->head = evenhead;          // 새 머리는 짝수 체인의 머리

}


///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
