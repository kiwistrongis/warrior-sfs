#include "blockio.h"
#include "inode.h"
#include "../assets.h"

int sfs_delete(char *pathname){
	inode* result;
	int ret = parse(pathname, result);
	if (ret < 0) //parse failed
		return ret; //file does not exist
	else {
		if((*result).type = 1)//file is directory
			if((*result).size > 0)
					//directories must be empty prior to deletion
				return -1;
		if(0/*file/dir is not open code later*/)
					//only closed files/directories can be deleted
				return -1;
		else {
			bfree((*result).index, (*result).size/128 + 1);
			//need to remove inode from parent itable
			return 1;}}}
