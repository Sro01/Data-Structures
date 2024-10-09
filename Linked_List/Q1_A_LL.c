//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
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
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
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

int insertSortedLL(LinkedList *ll, int item)
{
	ListNode *cur;
	ListNode *prev = cur;
	int index = 0;

	if (ll->head == NULL) {
		insertNode(ll, 0, item);
		return 0;
	}
	
	cur = ll->head;
	while(index < ll->size + 1) {
		if (cur == NULL) {
			insertNode(ll, ll->size, item);
			return ll->size - 1;
		}
		if (cur->item == item) {
			return -1;
		}
		if (cur->item > item) {
			insertNode(ll, index, item);
			return index;
		}
		cur = cur->next;
		index++;
	}
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;  // 현재 노드를 가리키는 포인터
	if (ll == NULL) // 리스트가 비어있으면 리턴
		return;
	cur = ll->head; // 현재 노드 포인터에 헤드 노드 저장

	if (cur == NULL) // 헤드노드가 없으면 비어있음
		printf("Empty");
	while (cur != NULL) // 노드의 끝까지
	{
		printf("%d ", cur->item); // 현재 값을 출력
		cur = cur->next; // 다음 노드로 이동
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head; // 헤드 노드부터 저장
	ListNode *tmp; // 노드를 가리키는 포인터

	while (cur != NULL){ // 노드의 끝까지
		tmp = cur->next; // tmp는 다음 노드를 가리킴
		free(cur); // 현재 노드를 해제
		cur = tmp; // 다음 노드로 이동
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp; // 노드를 가리키는 포인터

	if (ll == NULL || index < 0 || index >= ll->size) // 리스트가 비어있거나 인덱스가 범위 밖이면
		return NULL;

	temp = ll->head; // 헤드노드 저장

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next; // 다음 노드로 이동
		if (temp == NULL)  // 노드 끝을 만나면 리턴
			return NULL;
		index--;	// head부터 index까지 index번 반복하며 해당 노드의 메모리 주소를 반환
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
