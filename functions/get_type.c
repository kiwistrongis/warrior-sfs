#include "../warrior-sfs-lib.h"

int sfs_gettype(char *pathname){
	if(DEBUG) printf("%d\n",24);
	inode* result;
	if(DEBUG) printf("%d\n",25);
	int ret = parse(pathname,result);
	if (ret<0)
		return ret;
	else
		return (*result).type;}
