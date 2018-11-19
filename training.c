#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct Node {//-----------------------------------���� ���� �ԷµǾ� ������ ����Ʈ
	char character;
	struct Node* next;
}Node;

typedef struct Node2 {//-----------------------------------���� ������������� �ٲ�� ����Ǵ� ����Ʈ
	char character;
	struct Node2* next;
}Node2;

int main() {

	Node* head = NULL;//---------------------------------���� ����� ����Ʈ�� ù ��� �ּ�
	Node* tail = NULL;//---------------------------------���� ����� ����Ʈ�� ������ ��� �ּ�

	Node2* head2 = NULL;//---------------------------------��������� ����Ʈ�� ù ��� �ּ�
	Node2* tail2 = NULL;//---------------------------------��������� ����Ʈ�� ������ ��� �ּ�

	int size=0;//------------------------------------------��������Ʈ�� ����� �˱����ؼ�
	char temp=NULL; 
	//---------------------------------------------------��������� ����Ʈ�� �Է¹ޱ�
	printf("write num\n");
	while (temp != '\n') {
		Node* newnode = (Node*)malloc(sizeof(Node)); //������
		temp = getchar();
		newnode->character = temp;
		newnode->next = NULL;

		if (head == NULL)
			head = newnode;
		else
			tail->next = newnode;

		tail = newnode;
		size++;
	}
	//---------------------------------------------------��������� ����Ʈ�� �Է¹ޱ�
	//---------------------------------------------------��������� ����Ʈ ����ϱ�(����� ����� Ȯ�����ؼ�)
	//---------------------------------------------------���鹮�ڿ� ��Ÿ ����ó���� ���Ŀ� �߰��ϱ�
	//---------------------------------------------------���鹮�ڿ� ��Ÿ ����ó���� ���Ŀ� �߰��ϱ�
	Node* temp1 = (Node*)malloc(sizeof(Node)); //HEAD �̵��� head������ �ּҸ� �ؾ�����Ƿ� temp1�� ����� �̵���Ű�� �����.
	temp1 = head;

	while (temp1 != tail) {
		printf("[%c]", temp1->character);
		temp1 = temp1->next;
	}
	free(temp1);
	//---------------------------------------------------��������� ����Ʈ ����ϱ�(����� ����� Ȯ�����ؼ�)
	//---------------------------------------------------��������� ����Ʈ�� ��������� ����Ʈ�� �ٲپ�ֱ�.
	temp = NULL;
	Node* temp2 = (Node*)malloc(sizeof(Node));//HEAD �̵��� head������ �ּҸ� �ؾ�����Ƿ� temp2�� ����� �̵���Ű�� ���� ��´�..
	temp2 = head;

	while (size) {
			Node2* newnode2 = (Node2*)malloc(sizeof(Node2));
			if (isdigit(temp2->character)||temp2->character == '.')
			{
				newnode2->character = temp2->character;
				newnode2->next = NULL;

				tail2 = newnode2;
			}
			else
			{
				switch (newnode2->character) //tok = character
				{
				case '(':
					newnode2->character = temp2->character;
					newnode2->next = temp2;

					temp2 = newnode2;
					break;

				case ')':
					while (1)
					{
						popOp = SPop(&stack);
						if (popOp == '(')
							break;
						convExp[idx++] = popOp;
					}
					break;

				case '+': case '-':
				case '*': case '/':
					while (!SIsEmpty(&stack) && WhoPrecOp(SPeek(&stack), tok) >= 0)
						convExp[idx++] = SPop(&stack);

					SPush(&stack, tok);
					break;
				}
			}
			temp = getchar();
			newnode2->character = temp;
			newnode2->next = NULL;

			if (head == NULL)
				head = newnode2;
			else
				tail->next = newnode2;

			tail = newnode2;
			size--;
	}
	//---------------------------------------------------��������� ����Ʈ�� ��������� ����Ʈ�� �ٲپ�ֱ�.
	//---------------------------------------------------����Ʈ�� �迭�� �ű��
	//---------------------------------------------------����Ʈ�� �迭�� �ű��
	//---------------------------------------------------����ϱ�
	//---------------------------------------------------����ϱ�
	//---------------------------------------------------���
	//---------------------------------------------------���
	char* str;
	str = (char*)malloc(sizeof(char)*size);
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
