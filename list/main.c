#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void error(char* message) {
	fprintf(stderr, "%s", message);
	return;
}


ListNode* insert(ListNode* head, int pos, element value) {
	int k = pos;
	int move = 0;
	if (k == 0) {
		ListNode* p = (ListNode*)malloc(sizeof(ListNode));
		p->data = value;
		p->link = head;
		head = p;
		printf("\nMove along the link: %d\n", move);
		return head;
	}

	ListNode* pre = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	while (k > 1 && pre != NULL) {
		pre = pre->link;
		k--;
	}

	if (pre == NULL) {
		free(p);
		printf("\nMove along the link: %d\n", move);
		return head;
	}

	p->link = pre->link;
	pre->link = p;


	ListNode* temp = head;
	while (temp != pre->link) {
		temp = temp->link;
		move++;
	}
	printf("\nMove along the link: %d\n", move);

	return head;
}

ListNode* delete(ListNode* head, int pos) {
	int k = pos;
	int move = 0;

	if (k == 0) {
		ListNode* garbage;
		if (head == NULL) return NULL;
		garbage = head;
		head = garbage->link;
		free(garbage);
		printf("\nMove along the link: %d\n", move);
		return head;
	}

	ListNode* temp = head;
	ListNode* garbage = NULL;

	while (k > 1 && temp != NULL) {
		temp = temp->link;
		k--;
		move++;
	}

	if (temp == NULL || temp->link == NULL)
		return head;

	garbage = temp->link;
	temp->link = garbage->link;
	free(garbage);

	move++; 
	printf("\nMove along the link: %d\n", move);

	return head;
}

void print_list(ListNode* head) {
	printf("List: ");
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("\n");
}

int get_length(ListNode* head) {
	int length = 0;
	ListNode* current = head;
	while (current != NULL) {
		length++;
		current = current->link;
	}
	return length;
}

int main(void) {
	ListNode* head = NULL;
	int pos;
	element value;

	int answer;

	while (1) {
		printf("Menu\n");
		printf("(1) Insert\n");
		printf("(2) Delete\n");
		printf("(3) Print\n");
		printf("(0) Exit\n");
		printf("Enter the menu: ");
		scanf_s("%d", &answer);

		if (answer > 3 || answer < 0) {
			error("Invalid Menu. Please select again..\n");
		}
		else if (answer == 0) {
			printf("Exit the program.\n\n");
			exit(1);
		}
		else if (answer == 1) {
			printf("Enter the number and position: ");
			scanf_s("%d %d", &value, &pos);
			if (head == NULL && pos != 0) {
				printf("List is empty. Insert at position 0..\n");
				pos = 0;
			}
			else if (head != NULL && pos > get_length(head)) {
				printf("The last index is %d. Insert at the end of the list..\n", get_length(head)-1);
				pos = get_length(head);
			}
			head = insert(head, pos, value);
		}
		else if (answer == 2) {
			if (head == NULL) {
				error("List is empty\n");
			}
			else {
				printf("Enter the position to delete: ");
				scanf_s("%d", &pos);
				printf("\n");
				head = delete(head, pos);  
			}
		}
		else if (answer == 3) {
			print_list(head);
		}
		printf("\n");
	}
}