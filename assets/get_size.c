#include "inode.h"
#include "../assets.h"

int sfs_getsize(char *pathname){
	inode* result;
	inode hold;
	int ret = parse(pathname,result);
	if (ret >= 0){
		hold = *result;
		return hold.size;}
	else
		return -1;}
