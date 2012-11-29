#include "inode.h"
#include "../assets.h"

int sfs_gettype(char *pathname){
	inode* result;
	int ret = parse(pathname,result);
	if (ret<0)
		return ret;
	else
		return (*result).type;}
