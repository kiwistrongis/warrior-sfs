#include "blockio.h"
#include "../assets.h"

int sfs_delete(char *pathname){
	inode* result;
	int ret = parse(pathname, result);
	if (red >= 0)
	{
		if(*result.type = 1)//directory
		{
			if(*result.size = 0)//directory needs to be empty
			{
				//need to remove inode for empty directory
				return 1;
			}
			else //only empty directories can be deleted
			{
				return -1;
			}
		}
		else //file
		{
			bfree(*result.index, *result.size);
			//need to remove inode for file
		}
	}
}
