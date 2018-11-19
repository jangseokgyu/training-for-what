#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct Node {//먼저 infix 식이 입력되어 들어오는 리스트
	char character;
	struct Node* next;
}Node;

typedef struct Node2 {//식이 후위연산식으로 바뀌어 저장되는 리스트
	char character;
	struct Node2* next;
}Node2;

//########################################################후위연산식으로 바꾸기위한 구조체와 함수들 모음

typedef struct Operator_Stack {//연산자를 쌓아둘 스택(아직 리스트에 저장하는 것은 연구필요 어쩔수 없이 Stack[100]으로 100개의 스택에 저장함(유한한 연산자 저장가능-무리수식은 아님)
	char Stack[100];
	int top;
}Operator_Stack;

void init(Operator_Stack *s) {
	s->top = -1;
}

void push(Operator_Stack *s, char operator) {//스택에서 연산자를 넣고 top의 층을 높힌다
	s->Stack[++(s->top)] = operator;
}

char pop(Operator_Stack *s) {//스택에서 연산자를 꺼내고 top의 층을 낮춘다.
	return s->Stack[(s->top)--];
}

char peek(Operator_Stack *s) {//스택에서 제일 꼭대기 층의 연산자를 꺼내지않고 무엇인지 확인만 한다.
	return s->Stack[s->top];
}

int isEmpty(Operator_Stack *s) {//스택이 비었다면 0이아닌 수를, 비었다면 0을 반환
	return s->top == -1;
}

int precedence(char operator) {//연산자들의 우선순위를 반환 (,)는 가장 우선순위가 낮고, +,-가 그다음으로 높고 *,/가 제일 높다. 
	switch (operator) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return 999;
}
//#####################################################후위연산자로 바꾸기위한 구조체와 함수들 모음
int main() {

	Node* head = NULL;//---------------------------------중위 연산식 리스트의 첫 노드 주소
	Node* tail = NULL;//---------------------------------중위 연산식 리스트의 마직막 노드 주소

	Node2* head2 = NULL;//---------------------------------후위연산식 리스트의 첫 노드 주소
	Node2* tail2 = NULL;//---------------------------------후위연산식 리스트의 마지막 노드 주소

	int size=0;//----------------------------------------중위리스트의 사이즈를 알기위해서
	char temp='\0'; //temp != '\n'의 조건식을 만드려면 매개가 있어야한다.
	//+++++++++++++++++++++++++++++++++++++++++++++++++++중위연산식 리스트에 입력받기
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
  //---------------------------------------------------공백문자와 기타 예외처리식 추후에 추가하기
	//---------------------------------------------------공백문자와 기타 예외처리식 추후에 추가하기
	//+++++++++++++++++++++++++++++++++++++++++++++++++++중위연산식 리스트에 입력받기


	//+++++++++++++++++++++++++++++++++++++++++++++++++++중위연산식 리스트 출력하기(제대로 됬는지 확인위해서)
	Node* temp1 = (Node*)malloc(sizeof(Node)); //HEAD 이동시 head고유의 주소를 잊어버리므로 temp1을 만들어 이동시키며 출력함.
	temp1 = head;

	while (temp1 != tail) {
		printf("%c", temp1->character);
		temp1 = temp1->next;
	}
	printf("\n\n");
	//+++++++++++++++++++++++++++++++++++++++++++++++++++중위연산식 리스트 출력하기(제대로 됬는지 확인위해서)


	//+++++++++++++++++++++++++++++++++++++++++++++++++++중위연산식 리스트를 후위연산식 리스트에 바꾸어넣기.
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
				switch (temp2->character)
				{
				case '(':
					push(&s, temp2->character);
					break;

				case ')':
					returned_operator = pop(&s);
					while (returned_operator != '(') {//'('을 만날동안 스택에 쌓인 연산자를 꺼내서 노드에 저장해야하는데 while문이 한번돌때마다 하나의 노드를 만들게 되어 있어 노드를 안에서 새로 생성하는데에 구현이 아직 안되고있다.
						newnode2->character = returned_operator;
						returned_operator = pop(&s);
					}
					break;

				case '+': case '-':
				case '*': case '/':
					while(!isEmpty(&s) && (precedence(temp2->character) <= precedence(peek(&s)))) {//스택 꼭대기의 연산자와 그위에 쌓인 연산자를 비교하여 스택안의 연산자의 우선순위가 더높다면 다 스택의 연산자들을 다꺼내서 노드에 저장해야하는데 while문이 한번돌때마다 하나의 노드를 만들게 되어 있어 노드를 안에서 새로 생성하는것에대해 구현이 아직 안되고있다.
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

	while (!isEmpty(&s)) {//스택에 남은 연산자를 전부다 꺼내서 node의 끝에 연결해주어야하는데 구상이 아직안됨
    Node2* newnode4 = (Node2*)malloc(sizeof(Node2));
    newnode4->character = pop(&s);
    tail2 = newnode4;
    tail2 = tail2->next;
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++중위연산식 리스트를 후위연산식 리스트에 바꾸어넣기.


	//+++++++++++++++++++++++++++++++++++++++++++++++++++후위연산식 출력해보기
Node2* temp3 = (Node2*)malloc(sizeof(Node2)); //HEAD 이동시 head고유의 주소를 잊어버리므로 temp3을 만들어 이동시키며 출력함.
	temp3 = head2;

	while (temp3 != tail2) {
		printf("%c", temp3->character);
		temp3 = temp3->next;
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++후위연산식 출력해보기


	//+++++++++++++++++++++++++++++++++++++++++++++++++++후위연산식 리스트 계산하기

  /*리스트를 배열로 옮겨 계산한다면 소숫점 위치를 신경쓸 필요없이 연산할 수 있으나 오차가 발생하고 속도가 느리며 무리수 표현에 있어 한계가 있다. 그러니 리스트에 들어 있는채로 계산해야한다. 모 18한번이 리스트의 제일 끝 숫자부터 하나씩 연산해가면 가능하다고 했다. 본인이 직접 구현하진 않았다고 한다. 소숫점을 중심으로 수를 비교하여 길이가 다른 부분에는 0을 넣어 새로 리스트를 짠다. +는 그냥 연산하면되고 -는 큰 수가 앞에 오도록하고 부호 노드를 만들어 추후 부호를 추가하는 식으로 만들면된다고한다. 물론 말은 쉽다.
  */
	//+++++++++++++++++++++++++++++++++++++++++++++++++++후위연산식 리스트 계산하기


	//+++++++++++++++++++++++++++++++++++++++++++++++++++출력
  /*연산의 결과도 무리수이기에 계산하면서 출력하는게 가장 이상적이리라 생각된다. 물론 말은 쉽다.
  */
	//+++++++++++++++++++++++++++++++++++++++++++++++++++출력
	return 0;
}
