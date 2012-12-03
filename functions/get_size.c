#include "../warrior-sfs-lib.h"

int sfs_getsize(char *pathname){
	if(DEBUG) printf("%d\n",22);
	inode* result;
	int ret = parse(pathname,result);
	if(DEBUG) printf("%d\n",23);
	if (ret<0)
		return ret;
	else
		return (*result).size;}
