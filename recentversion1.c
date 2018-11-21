#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
	char val;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;//----------------
	int size;
} DLL;

Node *newnode(char n)
{
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->val = n;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

DLL *newDLL() {
	DLL *temp = (DLL *)malloc(sizeof(DLL));
	temp->head = NULL;
	temp->tail = NULL;//----------
	temp->size = 0;
	return temp;
}

void append(DLL *list, Node *newnode) {
	struct Node* temp = list->head;
	struct Node* newNode = newnode;
	if (list->head == NULL) {
		list->head = newNode;
		list->tail = newNode;//---------------------
		list->size++;
		return;
	}
	while (temp->next != NULL) {
		temp = temp->next;
	}
	list->size++;
	temp->next = newNode;
	list->tail = temp;//------------------
	newNode->prev = temp;
}

void insertAt(DLL *list, int index, Node *newnode) {

	struct Node* temp = list->head;

	if (index < 0 || index > list->size) {
		printf("INSERT ERROR: Out of Bound\n");
	}
	else if (index == 0) {
		newnode->next = list->head;
		list->head->prev = newnode;
		list->head = newnode;
		list->size++;
	}
	else if (index == list->size) {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		newnode->prev = temp;
		newnode->next = NULL;
		temp->next = newnode;
		list->size++;
	}
	else {
		for (int i = 0; i < index - 1; i++) {
			temp = temp->next;
		}
		list->tail = temp;//----------------------------
		newnode->prev = temp;
		newnode->next = temp->next;
		temp->next->prev = newnode;
		temp->next = newnode;
		list->size++;
	}
}

void deleteAt(DLL *list, int index) {

	struct Node* temp = list->head;

	if (index < 0 || index >= list->size) {
		printf("DELETE ERROR: Out of Bound\n");
	}
	else if (index == 0) {
		temp->next->prev = NULL;
		list->head = temp->next;
		list->size--;
	}
	else if (index + 1 == list->size) {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->prev->next = NULL;
		free(temp);

		list->size--;
	}

	else {
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}

		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		free(temp);

		list->size--;
	}

}

void print(DLL *list) {
	struct Node* temp = list->head;
	printf("Forward: ");
	while (temp != NULL) {
		printf("%c ", temp->val);
		temp = temp->next;
	}
	printf("\n");
}
//공백 문자와 마지막 '\n'문자를 제거하는 함수
void erasewhitespace(DLL *list) {
	int i = 0;

	struct Node* temp = list->head;
	while (temp->val != '\n') {
		if (isspace(temp->val)) {
			deleteAt(list, i);
			i--; //한 노드가 지워질 때마다 size가 줄어듬으로 index에서 1을 줄여준다.
			list->size--;//list에서 size도 줄어듬
		}
		temp = temp->next;
		i++;
	}
	deleteAt(list, i);//마지막 '\n'문자도 제거
	list->size--;//list에서 size도 줄어듬
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
//------------------------------------------------------------------------------------------------
/*
void ConvToRPNExp(DLL* list)
{
	Node* temp = (Node*)malloc(sizeof(Node));//HEAD 이동시 head고유의 주소를 잊어버리므로 temp을 만들어 이동시키며 값을 얻는다..
	temp = list->head;

	Operator_Stack s;
	char returned_operator; // ()시 연산자를 저장하고 옮기기위한 또하나의 temp
	init(&s);//스택초기화
	int size_temp = list->size;//size--로 연산 수를 정하므로 size_temp로 연산
	int initial_size = list->size;//원본의 사이즈를 추후 연산을 위해 저장해놓는다.
	while (size_temp) {
		Node* newnode1 = (Node*)malloc(sizeof(Node));//새로운 노드 생성
		newnode1 = temp;
		if (isdigit(temp->val) || temp->val == '.')//수와 '.'은 operator stack에 쌓지 않고 바로 node로 이동
		{
			insertAt(list, list->size, newnode1);//끝단에 추가해주기.
			list->size++;
		}
		else
		{
			switch (temp->val)
			{
			case '(':
				push(&s, temp->val);//스택에 '('쌓기
				break;

			case ')':
				returned_operator = pop(&s);
				while (returned_operator != '(') {//'('을 만날동안 스택에 쌓인 연산자를 꺼내서 추가노드에 저장.
					Node* newnode2 = (Node*)malloc(sizeof(Node));//새로운 노드 생성
					newnode2->val = returned_operator;
					insertAt(list, list->size, newnode2);
					returned_operator = pop(&s);
					list->size++;
				}
				break;

			case '+': case '-':
			case '*': case '/':
				while (!isEmpty(&s) && (precedence(temp->val) <= precedence(peek(&s)))) {
					Node* newnode3 = (Node*)malloc(sizeof(Node));//새로운 노드 생성
					newnode3->val = pop(&s);
					insertAt(list, list->size, newnode3);
					list->size++;
				}
				push(&s, temp->val);
				break;

			default:
				newnode1->val = temp->val;
				insertAt(list, list->size, newnode);
				list->size++;
				break;
			}
		}
		temp = temp->next;
		size_temp--;
	}

	while (!isEmpty(&s)) {//스택에 남은 연산자를 전부다 꺼내서 node의 끝에 연결해주어야하는데 구상이 아직안됨
		Node* newnode4 = (Node*)malloc(sizeof(Node));
		newnode4->val = pop(&s);
		insertAt(list, list->size, newnode4);
		list->size++;
	}
	int i = 0;
	while (initial_size) {
		deleteAt(list, i++);
		initial_size--;
		list->size--;
	}
}
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main() {
	DLL *list = newDLL();
	printf("please insert documents :\n");

	char characters='\0';
	while (characters != '\n') {
		characters = getchar();
		append(list, newnode(characters));
	}//마지막 노드에 '\n'이 들어간 상태
	erasewhitespace(list);//쓰잘데기 없는 것들 지우기
	print(list);
	//-------------------------------------------------------------------------------------------------------------------
	Node* temp = (Node*)malloc(sizeof(Node));//HEAD 이동시 head고유의 주소를 잊어버리므로 temp을 만들어 이동시키며 값을 얻는다..
	temp = list->head;

	Operator_Stack s;
	char returned_operator; // ()시 연산자를 저장하고 옮기기위한 또하나의 temp
	init(&s);//스택초기화
	int size_temp = list->size+1;//size--로 연산 수를 정하므로 size_temp로 연산
	int initial_size = list->size+1;//원본의 사이즈를 추후 연산을 위해 저장해놓는다.
	while (size_temp) {
		Node* newnode1 = (Node*)malloc(sizeof(Node));//새로운 노드 생성
		newnode1 = temp;
		if (isdigit(temp->val) || temp->val == '.')//수와 '.'은 operator stack에 쌓지 않고 바로 node로 이동
		{
			append(list, newnode(temp->val));//끝단에 추가해주기.
		}
		else
		{
			switch (temp->val)
			{
			case '(':
				push(&s, temp->val);//스택에 '('쌓기
				break;

			case ')':
				returned_operator = pop(&s);
				while (returned_operator != '(') {//'('을 만날동안 스택에 쌓인 연산자를 꺼내서 추가노드에 저장.
					append(list, newnode(returned_operator));
					returned_operator = pop(&s);
				}
				break;

			case '+': case '-':
			case '*': case '/':
				while (!isEmpty(&s) && (precedence(temp->val) <= precedence(peek(&s)))) {
					append(list, newnode(pop(&s)));
				}
				push(&s, temp->val);
				break;
			}
		}
		temp = temp->next;
		size_temp--;
	}

	while (!isEmpty(&s)) {//스택에 남은 연산자를 전부다 꺼내서 node의 끝에 연결해주어야하는데 구상이 아직안됨
		append(list, pop(&s));
	}
	/*int i = 0;
	while (initial_size) {
		deleteAt(list, i++);
		initial_size--;
		list->size--;
	}*/

	print(list);

	return 0;
}
