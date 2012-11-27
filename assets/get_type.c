#include "inode.h"
#include "../assets.h"

int sfs_gettype(char *pathname){
	inode* result;
	int ret = parse(pathname,result);
	if (ret >= 0){
		return (*result).type;}
	else
		return -1;}
