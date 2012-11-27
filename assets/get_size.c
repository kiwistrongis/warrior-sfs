#include "inode.h"
#include "../assets.h"

int sfs_getsize(char *pathname){
	inode* result;
	int ret = parse(pathname,result);
	if (ret >= 0){
		return (*result).size;}
	else
		return -1;}
