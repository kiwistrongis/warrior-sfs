#include "blockio.h"
#include "inode.h"
#include "../assets.h"

int sfs_open(char *pathname){
	inode* result;
	int ret = parse(pathname, result);
	if (ret >= 0)
		return set_open(result);
	else	
		return -1;}
