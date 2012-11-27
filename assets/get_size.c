#include "inode.h"
#include "../assets.h"

int sfs_getsize(char *pathname){
	inode* result;
	inode test;
	int ret = parse(pathname,result);
	if (ret >= 0){
		test = *result;
		return test.size;}
	else
		return -1;}
