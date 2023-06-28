#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE = 0,TRUE }boolType_t;
typedef enum { SUCCESS = 0, INVALID_INDEX,EMPTY_LIST }statusType;
typedef enum { INSERT_FRONT = 1, INSERT_END, INSERT_AT, DELETE_FRONT, DELETE_END, DELETE_AT, SEARCH_NODE, DISPLAY_LTR,DISPLAY_RTL}opeartionType;

struct Node {
	int data;
	struct Node *next;
	struct Node *prev;
};
struct Node* head = NULL;
struct Node* createNode(int myData) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = myData;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;

}
void insertAtFront(int myData) {
	struct Node* t = head;
	struct Node* newNode = createNode(myData);
	if (t == NULL) {
		head = newNode;
		head->next = head;
		head->prev = head;
	}
	else {
		struct Node* lastNode = t->prev;
		t->prev = newNode;
		newNode->next = t;
		newNode->prev = lastNode;
		lastNode->next = newNode;
		head = newNode;
	}
}
void insertAtEnd(int myData) {
	struct Node* t = head;
	struct Node* newNode = createNode(myData);
	if (t == NULL) {
		head = newNode;
		head->next = head;
		head->prev = head;
	}
	else {
		while (t->next != head)
			t = t->next;
		t->next = newNode;
		newNode->prev = t;
		newNode->next = head;
		head->prev = newNode;
	}
}
boolType_t search(int myData) {
	struct Node* temp = head;
	if (temp == NULL)
		return FALSE;
	else {
		while (temp->next != head) {
			if (temp->data == myData)
				return TRUE;
			temp = temp->next;
		}
		if (temp->data == myData)
			return TRUE;
	}
	return FALSE;
}
statusType insertAt(int myData, int pos) {
	struct Node* t = head;
	struct Node* newNode = createNode(myData);
	statusType status = INVALID_INDEX;

		if (t == NULL) {
			if (pos == 0) {
				head = newNode;
				head->next = newNode;
				head->prev = newNode;
				return SUCCESS;
			}
			else
				return INVALID_INDEX;
		}
		else {
			if (t->next == head) {
				insertAtFront(myData);
				return SUCCESS;
			}
		
			int count = 1;
			while (t != head) {
				count++;
				if (count == pos) {
					status = SUCCESS;
					break;
				}
				t = t->next;
			}
			if (status == SUCCESS) {
				struct Node* tmp = t->next;
				t->next = newNode;
				newNode->prev = t;
				newNode->next = tmp;
				tmp->prev = newNode;
				return status;
			}
			else
				return status;
		}
}
boolType_t deleteFirst() {
	if (head == NULL)
		return FALSE;

	else {
		if (head->next == head)
		{
			free(head);
			head = NULL;
			return TRUE;
		}
		struct Node* t = head->next;
		struct Node* t1 = head->prev;
		free(head);
		head = t;
		head->prev = t1;
		t1->next = t;
	}
	return TRUE;
}
boolType_t deleteLast() {
	struct Node* tmp = head;
	if (tmp == NULL)
		return FALSE;
	else {
		while (tmp->next != head) 
			tmp = tmp->next;
		if (tmp->next == tmp)
		{
			free(head);
			head = NULL;
			return TRUE;
		}
		struct Node* tempLast = tmp->prev;
		tempLast->next = head;
		head->prev = tempLast;
		free(tmp);
		return TRUE;
	}
}
statusType deleteAt(int pos) {
	struct Node* temp = head;
	statusType status = INVALID_INDEX;
	if (temp == NULL)
		return EMPTY_LIST;
	else {
		int count = 0;
		while (temp->next != head) {
			count++;
			temp = temp->next;
			if (count == pos) {
				status = SUCCESS;
				break;
			}
		}
		if (status == SUCCESS) {
			struct Node* tempNext = temp->next;
			struct Node* tempPrev = temp->prev;
			free(temp);
			tempPrev->next = tempNext;
			tempNext->prev = tempPrev;

		}
		return status;
	}
}

void display(opeartionType op) {
	struct Node* temp = head;
	if (temp == NULL) {
		printf("The list is empty!\n");
		return;
	}
	if (op == DISPLAY_LTR) {
		while (temp->next != head) {
			printf("%d ", temp->data);
			temp = temp->next;
		}
	}
	if (op == DISPLAY_RTL) {
		struct Node* temp = head->prev;
		while (temp != head) {
			printf("%d ", temp->data);
			temp = temp->prev;
		}
	}
	printf("%d ", temp->data);
}
int main() {
	int choice;
	int data,pos;
	while (TRUE) {
		printf("\n1. insert node at front\n");
		printf("2. insert node at end\n");
		printf("3. insert node at specific position\n");
		printf("4. delete node at front \n");
		printf("5. delete node at end\n");
		printf("6. delete node at specific position\n");
		printf("7. search specific element\n");
		printf("8. display the list left to right\n");
		printf("9. display the list right to left\n");
		printf("Enter your choice...:");
		scanf("%d", &choice);
		switch (choice) {
		case INSERT_FRONT:
			printf("Enter data "); scanf("%d", &data);
			insertAtFront(data);
			break;
		case INSERT_END:
			printf("Enter data "); scanf("%d", &data);
			insertAtEnd(data);
			break;
		case INSERT_AT:
			printf("Enter position "); scanf("%d", &pos);
			printf("Enter data "); scanf("%d", &data);
			insertAt(data,pos);
			break;
		case DELETE_FRONT:
			if (deleteFirst())
				printf("delete operation succeeded!\n");
			else
				printf("couldn't delete the empty list!\n");
			break;
		case DELETE_END:
			if(deleteLast(data))
				printf("Delete operation succeeded!\n");
			else
				printf("couldn't delete empty list!\n");
			break;
		case DELETE_AT:
			printf("Enter position "); scanf("%d", &pos);
			statusType status = deleteAt(pos);
			if (status == SUCCESS)
				printf("delete operation succeeded!\n");
			else if (status == EMPTY_LIST)
				printf("The list is empty!\n");
			else
				printf("Invalid index!\n");
			break;
		case SEARCH_NODE:
			printf("Enter the element to be sought");
			scanf("%d", &data);
			if (search(data))
				printf("Element found in the list!\n");
			else
				printf("Element not found in the list!\n");
			break;
		case DISPLAY_LTR:
			display(DISPLAY_LTR);
			break;
		case DISPLAY_RTL:
			display(DISPLAY_RTL);
			break;

		}
	}
	return 0;
}