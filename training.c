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

int main() {

	Node* head = NULL;//---------------------------------중위 연산식 리스트의 첫 노드 주소
	Node* tail = NULL;//---------------------------------중위 연산식 리스트의 마직막 노드 주소

	Node2* head2 = NULL;//---------------------------------후위연산식 리스트의 첫 노드 주소
	Node2* tail2 = NULL;//---------------------------------후위연산식 리스트의 마지막 노드 주소

	int size=0;//------------------------------------------중위리스트의 사이즈를 알기위해서
	char temp=NULL; 
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
		printf("[%c]", temp1->character);
		temp1 = temp1->next;
	}
	free(temp1);
	//---------------------------------------------------중위연산신 리스트 출력하기(제대로 됬는지 확인위해서)
	//---------------------------------------------------중위연산식 리스트를 후위연산식 리스트에 바꾸어넣기.
	temp = NULL;
	Node* temp2 = (Node*)malloc(sizeof(Node));//HEAD 이동시 head고유의 주소를 잊어버리므로 temp2을 만들어 이동시키며 값을 얻는다..
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
	//---------------------------------------------------중위연산식 리스트를 후위연산식 리스트에 바꾸어넣기.
	//---------------------------------------------------리스트를 배열로 옮기기
	//---------------------------------------------------리스트를 배열로 옮기기
	//---------------------------------------------------계산하기
	//---------------------------------------------------계산하기
	//---------------------------------------------------출력
	//---------------------------------------------------출력
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
