#include "../assets.h"
#include "../assets/inode.h"
#include <stdio.h>
int main(){
	inode* t = malloc(sizeof(inode)*3);
	//a
	t[0].index = 3;
	t[0].size = 1;
	t[0].type = 0;
	t[0].name = "asdf";
	//b
	t[1].index = 3;
	t[1].size = 1;
	t[1].type = 0;
	t[1].name = "fdsa";
	//n
	t[2].index = 0;
	t[2].size = 0;
	t[2].type = 0;
	t[2].name = "";
	
	char* s = malloc(sizeof(char)*100);
	int ret = write_itable( s, t, 100);
	if(ret<0) return;
	int k;
	free(t);
	
	ret = read_itable( s, (inode**)&t, ret);
	printf("%d\n",ret);
	if(ret<0) return;
	for(k = 0; k < 3; k++)
		printf("%d %d %d %s\n",
			t[k].index, t[k].size, t[k].type, t[k].name);
	return 0;
}
