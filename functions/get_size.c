#include "../warrior-sfs-lib.h"

int sfs_getsize(char *pathname){
	inode* result;
	int ret = parse(pathname,result);
	if (ret<0)
		return ret;
	else
		return (*result).size;}
