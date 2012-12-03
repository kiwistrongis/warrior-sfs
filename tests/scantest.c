#include <stdio.h>
#include <stdlib.h>
int main(){
	int i = 0;
	char b = '0';
	printf("%d %c\n",i,b);
	char* s = malloc(sizeof(char)*16);
	scanf("%s",s);
	printf("%s\n",s);
	scanf("%d %c",&i,&b);
	printf("%d %c\n",i,b);
	return 0;}
