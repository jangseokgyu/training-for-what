#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct Node {//���� infix ���� �ԷµǾ� ������ ����Ʈ
	char character;
	struct Node* next;
}Node;

typedef struct Node2 {//���� ������������� �ٲ�� ����Ǵ� ����Ʈ
	char character;
	struct Node2* next;
}Node2;

//########################################################������������� �ٲٱ����� ����ü�� �Լ��� ����

typedef struct Operator_Stack {//�����ڸ� �׾Ƶ� ����(���� ����Ʈ�� �����ϴ� ���� �����ʿ� ��¿�� ���� Stack[100]���� 100���� ���ÿ� ������(������ ������ ���尡��-���������� �ƴ�)
	char Stack[100];
	int top;
}Operator_Stack;

void init(Operator_Stack *s) {
	s->top = -1;
}

void push(Operator_Stack *s, char operator) {//���ÿ��� �����ڸ� �ְ� top�� ���� ������
	s->Stack[++(s->top)] = operator;
}

char pop(Operator_Stack *s) {//���ÿ��� �����ڸ� ������ top�� ���� �����.
	return s->Stack[(s->top)--];
}

char peek(Operator_Stack *s) {//���ÿ��� ���� ����� ���� �����ڸ� �������ʰ� �������� Ȯ�θ� �Ѵ�.
	return s->Stack[s->top];
}

int isEmpty(Operator_Stack *s) {//������ ����ٸ� 0�̾ƴ� ����, ����ٸ� 0�� ��ȯ
	return s->top == -1;
}

int precedence(char operator) {//�����ڵ��� �켱������ ��ȯ (,)�� ���� �켱������ ����, +,-�� �״������� ���� *,/�� ���� ����. 
	switch (operator) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return 999;
}
//#####################################################���������ڷ� �ٲٱ����� ����ü�� �Լ��� ����
int main() {

	Node* head = NULL;//---------------------------------���� ����� ����Ʈ�� ù ��� �ּ�
	Node* tail = NULL;//---------------------------------���� ����� ����Ʈ�� ������ ��� �ּ�

	Node2* head2 = NULL;//---------------------------------��������� ����Ʈ�� ù ��� �ּ�
	Node2* tail2 = NULL;//---------------------------------��������� ����Ʈ�� ������ ��� �ּ�

	int size=0;//----------------------------------------��������Ʈ�� ����� �˱����ؼ�
	char temp='\0'; //temp != '\n'�� ���ǽ��� ������� �Ű��� �־���Ѵ�.
	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����Ʈ�� �Է¹ޱ�
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
  //---------------------------------------------------���鹮�ڿ� ��Ÿ ����ó���� ���Ŀ� �߰��ϱ�
	//---------------------------------------------------���鹮�ڿ� ��Ÿ ����ó���� ���Ŀ� �߰��ϱ�
	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����Ʈ�� �Է¹ޱ�


	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����Ʈ ����ϱ�(����� ����� Ȯ�����ؼ�)
	Node* temp1 = (Node*)malloc(sizeof(Node)); //HEAD �̵��� head������ �ּҸ� �ؾ�����Ƿ� temp1�� ����� �̵���Ű�� �����.
	temp1 = head;

	while (temp1 != tail) {
		printf("%c", temp1->character);
		temp1 = temp1->next;
	}
	printf("\n\n");
	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����Ʈ ����ϱ�(����� ����� Ȯ�����ؼ�)


	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����Ʈ�� ��������� ����Ʈ�� �ٲپ�ֱ�.
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
				switch (temp2->character)
				{
				case '(':
					push(&s, temp2->character);
					break;

				case ')':
					returned_operator = pop(&s);
					while (returned_operator != '(') {//'('�� �������� ���ÿ� ���� �����ڸ� ������ ��忡 �����ؾ��ϴµ� while���� �ѹ��������� �ϳ��� ��带 ����� �Ǿ� �־� ��带 �ȿ��� ���� �����ϴµ��� ������ ���� �ȵǰ��ִ�.
						newnode2->character = returned_operator;
						returned_operator = pop(&s);
					}
					break;

				case '+': case '-':
				case '*': case '/':
					while(!isEmpty(&s) && (precedence(temp2->character) <= precedence(peek(&s)))) {//���� ������� �����ڿ� ������ ���� �����ڸ� ���Ͽ� ���þ��� �������� �켱������ �����ٸ� �� ������ �����ڵ��� �ٲ����� ��忡 �����ؾ��ϴµ� while���� �ѹ��������� �ϳ��� ��带 ����� �Ǿ� �־� ��带 �ȿ��� ���� �����ϴ°Ϳ����� ������ ���� �ȵǰ��ִ�.
						newnode2->character = pop(&s);
          }
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

	while (!isEmpty(&s)) {//���ÿ� ���� �����ڸ� ���δ� ������ node�� ���� �������־���ϴµ� ������ �����ȵ�
    Node2* newnode4 = (Node2*)malloc(sizeof(Node2));
    newnode4->character = pop(&s);
    tail2 = newnode4;
    tail2 = tail2->next;
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����Ʈ�� ��������� ����Ʈ�� �ٲپ�ֱ�.


	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����غ���
Node2* temp3 = (Node2*)malloc(sizeof(Node2)); //HEAD �̵��� head������ �ּҸ� �ؾ�����Ƿ� temp3�� ����� �̵���Ű�� �����.
	temp3 = head2;

	while (temp3 != tail2) {
		printf("%c", temp3->character);
		temp3 = temp3->next;
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����غ���


	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����Ʈ ����ϱ�

  /*����Ʈ�� �迭�� �Ű� ����Ѵٸ� �Ҽ��� ��ġ�� �Ű澵 �ʿ���� ������ �� ������ ������ �߻��ϰ� �ӵ��� ������ ������ ǥ���� �־� �Ѱ谡 �ִ�. �׷��� ����Ʈ�� ��� �ִ�ä�� ����ؾ��Ѵ�. �� 18�ѹ��� ����Ʈ�� ���� �� ���ں��� �ϳ��� �����ذ��� �����ϴٰ� �ߴ�. ������ ���� �������� �ʾҴٰ� �Ѵ�. �Ҽ����� �߽����� ���� ���Ͽ� ���̰� �ٸ� �κп��� 0�� �־� ���� ����Ʈ�� §��. +�� �׳� �����ϸ�ǰ� -�� ū ���� �տ� �������ϰ� ��ȣ ��带 ����� ���� ��ȣ�� �߰��ϴ� ������ �����ȴٰ��Ѵ�. ���� ���� ����.
  */
	//+++++++++++++++++++++++++++++++++++++++++++++++++++��������� ����Ʈ ����ϱ�


	//+++++++++++++++++++++++++++++++++++++++++++++++++++���
  /*������ ����� �������̱⿡ ����ϸ鼭 ����ϴ°� ���� �̻����̸��� �����ȴ�. ���� ���� ����.
  */
	//+++++++++++++++++++++++++++++++++++++++++++++++++++���
	return 0;
}
