//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

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
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Q2. 두 개의 단일 연결 리스트를 번갈아가며 병합
// ll2의 노드들을 ll1의 각 노드 뒤에 번갈아 삽입
// 삽입은 ll1의 빈 자리(노드 사이)가 있을 때만 수행
// ll2가 먼저 소진되면 ll2는 빈 리스트가 됨
// ll1이 먼저 끝나면 ll2의 남은 노드는 그대로 유지
// 새 노드 생성 없이 기존 ll2의 노드를 잘라서 ll1에 연결
// 반환값 없음 (void 함수)

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	// 1. 예외 처리(ll1 또는 ll2가 NULL인 경우, 둘 중 하나라도 빈 리스트인 경우)
	if(!ll1 || !ll2) return;        
	if(ll1->head == NULL || ll2->head == NULL) return;

    // 2. 시작점 지정: ll1의 현재 위치(cur1)
	ListNode *cur1 = ll1->head;
	
	
    // 3. ll1에 남은 자리(cur1)와 ll2에서 꺼낼 노드(cur2)가 모두 있을 동안 반복
	while (cur1 && ll2->head) {

		//(1) ll2 맨 앞 노드(cur2) 꺼내기
		ListNode *cur2 = ll2->head;
		ll2->head = cur2->next;    // ll2의 head를 다음 노드로 옮김 (cur2는 ll2에서 분리됨)
		ll2->size--;               // ll2의 크기 감소
        
		// (2) ll1의 현재 노드(cur1) 뒤에 cur2를 삽입하기
		ListNode *next1 = cur1->next;   // cur1의 원래 다음 노드를 기억
		cur2->next = next1;             // cur2 뒤에 원래 cur1 다음 노드를 연결
		cur1->next = cur2;              // cur1 뒤에 cur2를 연결
		ll1->size++;                    // ll1의 크기 증가

		cur1 = next1;                   // 원래 있던 다음 노드로 이동
	}


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
