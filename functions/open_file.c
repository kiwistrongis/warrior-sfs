#include "../warrior-sfs-lib.h"

//open file specified by pathname; if it doesn't exist, error
//if file opens;return file descriptor(non-negative integer value) to caller

int sfs_open(char *pathname){
	inode* result;
	int ret = parse(pathname, result);
	if (ret >= 0)
		char * block = malloc(sizeof(char)*128)
		block = get_block(super.openFileTable_loc);
		int t_size = read_itable(block, (inode**)&result, 128*sizeof(char));
		
	else	
		return -1;}
