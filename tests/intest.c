#include "../assets.h"
#include "../assets/inode.h"
#include <stdio.h>
main(){
	inode i ={
		.index = 3,
		.size = 1,
		.type = 0};
	i.name = malloc(4*sizeof(char));
	i.name = "root";
	char* c = write_inode(i);
	printf("%s",c);
	
	inode j ={
		.index = 0,
		.size = 0,
		.type = 0};
	j.name = malloc(4*sizeof(char));
	j.name = "\0\0\0\0";
	j = read_inode(c);
	printf("%d %d %d %s\n",
		j.index, j.size, j.type, j.name);
}
