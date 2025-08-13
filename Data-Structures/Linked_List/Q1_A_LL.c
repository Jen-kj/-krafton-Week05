//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;                     // 데이터
	struct _listnode *next;       // 다음 노드 주소
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;                 // 크기
	ListNode *head;           // 첫 노드 주소
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;   // 연결 리스트
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list(연결 리스트 빈 리스트로 초기화)
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
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

//Q1. 사용자로부터 정수를 입력받아 오름차순 정렬된 단일 연결 리스트 삽입
// 중복값 삽입 X, 연결 리스트는 비어있거나 이미 오름차순 상태라고 가정
// 삽입 성공 -> 해당 값이 추가된 인덱스 위치 반환, 삽입 실패 -> -1 반환
int insertSortedLL(LinkedList *ll, int item)
{ 
	// 1. 리스트 자체가 없으면 실패
	if (ll == NULL)
	return -1;     

	int idx = 0;                   // '삽입 될 인덱스'를 세는 함수 초기화
	ListNode *cur = ll->head;     // '현재 가리키는 노드' (탐색 포인터0 (탐색 시작: head)

	// 2-1. 삽입될 위치 찾기 (처음으로 item 값 이상인 값이 나오는 위치)
	while (cur != NULL && cur->item < item) {
		cur = cur->next;     // 다음 노드로 이동
		idx++;                 // -> 한 칸 이동했으니 인덱스 +1
	}

	// 3. 중복 값 삽입 방지: 지금 가리키는 값이 item과 같으면 이미 존재 -> 실패(-1)
	if (cur != NULL && cur->item == item) 
		return -1;
	
	//4. 삽입할 노드 생성
	if (insertNode(ll, idx, item) == 0) return idx;
	return -1;

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
