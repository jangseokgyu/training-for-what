#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	char character;
	struct Node* next;
}Node;

int main() {
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