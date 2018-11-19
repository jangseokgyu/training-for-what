#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct Node {//-----------------------------------먼저 식이 입력되어 들어오는 리스트
	char character;
	struct Node* next;
}Node;

typedef struct Node2 {//-----------------------------------식이 후위연산식으로 바뀌어 저장되는 리스트
	char character;
	struct Node2* next;
}Node2;

//---------------------------------------------------------후위연산자로 바꾸기위한 구조체와 함수들 모음

typedef struct Operator_Stack {//-------------------------연산자를 쌓아둘 스택(아직 리스트에 저장하는 것은 연구필요)
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
//---------------------------------------------------------후위연산자로 바꾸기위한 구조체와 함수들 모음
int main() {

	Node* head = NULL;//---------------------------------중위 연산식 리스트의 첫 노드 주소
	Node* tail = NULL;//---------------------------------중위 연산식 리스트의 마직막 노드 주소

	Node2* head2 = NULL;//---------------------------------후위연산식 리스트의 첫 노드 주소
	Node2* tail2 = NULL;//---------------------------------후위연산식 리스트의 마지막 노드 주소

	int size=0;//----------------------------------------중위리스트의 사이즈를 알기위해서
	char temp='\0'; //temp != '\n'의 조건식을 만드려면 매개가 있어야한다.
	//---------------------------------------------------중위연산식 리스트에 입력받기
	printf("write num\n");
	while (temp != '\n') {
		Node* newnode = (Node*)malloc(sizeof(Node)); //노드생성
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
	//---------------------------------------------------중위연산식 리스트에 입력받기
	//---------------------------------------------------중위연산식 리스트 출력하기(제대로 됬는지 확인위해서)
	//---------------------------------------------------공백문자와 기타 예외처리식 추후에 추가하기
	//---------------------------------------------------공백문자와 기타 예외처리식 추후에 추가하기
	Node* temp1 = (Node*)malloc(sizeof(Node)); //HEAD 이동시 head고유의 주소를 잊어버리므로 temp1을 만들어 이동시키며 출력함.
	temp1 = head;

	while (temp1 != tail) {
		printf("%c ", temp1->character);
		temp1 = temp1->next;
	}
	printf("\n\n");
	//---------------------------------------------------중위연산식 리스트 출력하기(제대로 됬는지 확인위해서)
	//---------------------------------------------------중위연산식 리스트를 후위연산식 리스트에 바꾸어넣기.
	temp = '\0';
	Node* temp2 = (Node*)malloc(sizeof(Node));//HEAD 이동시 head고유의 주소를 잊어버리므로 temp2을 만들어 이동시키며 값을 얻는다..
	temp2 = head;
	Operator_Stack s;
	char returned_operator; // ()시 연산자를 저장하고 옮기기위한 또하나의 temp
	init(&s);
  
	while (size) {
			Node2* newnode2 = (Node2*)malloc(sizeof(Node2));//후위연산식에 새로 투입될 노드들을 위해 while문안에 노드2만들어준다.

			if (isdigit(temp2->character)||temp2->character == '.')//수와 '.'은 operator stack에 쌓지 않고 바로 node2로 이동
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
	//---------------------------------------------------중위연산식 리스트를 후위연산식 리스트에 바꾸어넣기.
	//---------------------------------------------------후위연산식 출력해보기
Node2* temp3 = (Node2*)malloc(sizeof(Node2)); //HEAD 이동시 head고유의 주소를 잊어버리므로 temp1을 만들어 이동시키며 출력함.
	temp3 = head2;

	while (temp3 != tail2) {
		printf("%c ", temp3->character);
		temp3 = temp3->next;
	}
	printf("\n\n");
	//---------------------------------------------------후위연산식 출력해보기
	//---------------------------------------------------리스트를 배열로 옮기기
	//---------------------------------------------------리스트를 배열로 옮기기
	//---------------------------------------------------계산하기
	//---------------------------------------------------계산하기
	//---------------------------------------------------출력
	//---------------------------------------------------출력
	return 0;
}
