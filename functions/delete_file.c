#include "../warrior-sfs-lib.h"

int sfs_delete(char* pathname){
	inode* file;
	int ret = parse(pathname, file);
	if (ret < 0) //parse failed
		return ret; //file does not exist
	int lastSlash = 0;
	int i;
	while((i = strchr(pathname + lastSlash + 1))!=NULL)
		lastSlash = i;
	char* dirpath = malloc(sizeof(char)*(lastSlash + 1));
	for(i = 0; i < lastSlash; i++)
		dirpath[i] = pathname[i];
	*(dirpath + 1) = '\0';
	inode* parent;
	ret = parse(dirpath, parent);
	if(ret < 0) return ret;
	
	
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
