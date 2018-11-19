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

//---------------------------------------------------------���������ڷ� �ٲٱ����� ����ü�� �Լ��� ����

typedef struct Operator_Stack {//-------------------------�����ڸ� �׾Ƶ� ����(���� ����Ʈ�� �����ϴ� ���� �����ʿ�)
	char Stack[10];
	int top;
}Operator_Stack;

void init(Operator_Stack *s) {
	s->top = -1;
}

void push(Operator_Stack *s, char operator) {
	s->Stack[++(s->top)] = operator;
}

char pop(Operator_Stack *s) {
	return s->Stack[(s->top)--];
}

char peek(Operator_Stack *s) {
	return s->Stack[s->top];
}

int isEmpty(Operator_Stack *s) {
	return s->top == -1;
}

int precedence(char operator) {
	switch (operator) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return 999;
}
//---------------------------------------------------------���������ڷ� �ٲٱ����� ����ü�� �Լ��� ����
int main() {

	Node* head = NULL;//---------------------------------���� ����� ����Ʈ�� ù ��� �ּ�
	Node* tail = NULL;//---------------------------------���� ����� ����Ʈ�� ������ ��� �ּ�

	Node2* head2 = NULL;//---------------------------------��������� ����Ʈ�� ù ��� �ּ�
	Node2* tail2 = NULL;//---------------------------------��������� ����Ʈ�� ������ ��� �ּ�

	int size=0;//----------------------------------------��������Ʈ�� ����� �˱����ؼ�
	char temp='\0'; //temp != '\n'�� ���ǽ��� ������� �Ű��� �־���Ѵ�.
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
		printf("%c ", temp1->character);
		temp1 = temp1->next;
	}
	printf("\n\n");
	//---------------------------------------------------��������� ����Ʈ ����ϱ�(����� ����� Ȯ�����ؼ�)
	//---------------------------------------------------��������� ����Ʈ�� ��������� ����Ʈ�� �ٲپ�ֱ�.
	temp = '\0';
	Node* temp2 = (Node*)malloc(sizeof(Node));//HEAD �̵��� head������ �ּҸ� �ؾ�����Ƿ� temp2�� ����� �̵���Ű�� ���� ��´�..
	temp2 = head;
	Operator_Stack s;
	char returned_operator; // ()�� �����ڸ� �����ϰ� �ű������ ���ϳ��� temp
	init(&s);
  
	while (size) {
			Node2* newnode2 = (Node2*)malloc(sizeof(Node2));//��������Ŀ� ���� ���Ե� ������ ���� while���ȿ� ���2������ش�.

			if (isdigit(temp2->character)||temp2->character == '.')//���� '.'�� operator stack�� ���� �ʰ� �ٷ� node2�� �̵�
			{
				newnode2->character = temp2->character;
			}
			else
			{
				switch (temp2->character) //tok = character
				{
				case '(':
					push(&s, temp2->character);
					break;

				case ')':
					returned_operator = pop(&s);
					while (returned_operator != '(') {
						newnode2->character = returned_operator;
						returned_operator = pop(&s);
					}
					break;

				case '+': case '-':
				case '*': case '/':
					while (!isEmpty(&s) && (precedence(temp2->character) <= precedence(peek(&s))))
						newnode2->character = pop(&s);

					push(&s, temp2->character);
					break;

				default:
					newnode2->character = temp2->character;
					break;
				}
			}
      if (head2 == NULL)
			  head2 = newnode2;
		  else
			  tail2->next = newnode2;

      tail2 = newnode2;
      temp2 = temp2->next;
			size--;
	}

	while (isEmpty(&s)) {
		tail2->character = pop(&s);
		tail2 = tail2->next;
	}
	//---------------------------------------------------��������� ����Ʈ�� ��������� ����Ʈ�� �ٲپ�ֱ�.
	//---------------------------------------------------��������� ����غ���
Node2* temp3 = (Node2*)malloc(sizeof(Node2)); //HEAD �̵��� head������ �ּҸ� �ؾ�����Ƿ� temp1�� ����� �̵���Ű�� �����.
	temp3 = head2;

	while (temp3 != tail2) {
		printf("%c ", temp3->character);
		temp3 = temp3->next;
	}
	printf("\n\n");
	//---------------------------------------------------��������� ����غ���
	//---------------------------------------------------����Ʈ�� �迭�� �ű��
	//---------------------------------------------------����Ʈ�� �迭�� �ű��
	//---------------------------------------------------����ϱ�
	//---------------------------------------------------����ϱ�
	//---------------------------------------------------���
	//---------------------------------------------------���
	return 0;
}
