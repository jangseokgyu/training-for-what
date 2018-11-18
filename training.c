#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct Node {
	char character;
	struct Node* next;
}Node;

int main() {

	Node* head = NULL;
	Node* tail = NULL;
	char temp=NULL; 

	printf("write num\n");

	while (temp != '\n') {
		Node* newnode = (Node*)malloc(sizeof(Node));
		temp = getchar();
		newnode->character = temp;
		newnode->next = NULL;

		if (head == NULL)
			head = newnode;
		else
			tail->next = newnode;

		tail = newnode;
	}
	Node* temp1 = (Node*)malloc(sizeof(Node));
	temp1 = head;

	while (temp1 != tail) {
		printf("[%c]", temp1->character);
		temp1 = temp1->next;q
	}

	int i;
	printf("write num\n");
	scanf("%d", &i);
	char* text;
	text = (char*)malloc(sizeof(text)*i);

	for (int a = 0; a < i; a++)
	{
		if (a == 0)
			text[0] = 'a';
		else
			text[a] = text[a - 1] + 1;
		printf("%c\n", text[a]);
	}
	free(text);

	return 0;
}
