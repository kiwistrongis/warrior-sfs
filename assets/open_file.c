#include "blockio.h"
#include "inode.h"
#include "../assets.h"

//open file specified by pathname; if it doesn't exist, error
//if file opens;return file descriptor(non-negative integer value) to caller

int sfs_open(char *pathname){
	inode* result;
	int ret = parse(pathname, result);
	if (ret >= 0)
		return set_open(result);
	else	
		return -1;}
