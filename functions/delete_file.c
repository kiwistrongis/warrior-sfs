#include "../warrior-sfs-lib.h"

int sfs_delete(char* pathname){
	if(DEBUG) printf("%d\n",60);
	//get the file's meta
	inode* file = malloc(sizeof(inode));
	int ret = parse(pathname, file);
	if (ret < 0) {//parse failed, file does not exist?
		free(file);
		return ret;}
	
	//get open file table
	if(DEBUG) printf("%d\n",61);
	inode** oft; //open file table
	char* oft_buffer = malloc(sizeof(char)*super.blockSize);
	ret = get_block( super.openFileTable_loc, oft_buffer);
	if(DEBUG) printf("%d\n",62);
	if (ret < 0) {
		free(file);
		free(oft_buffer);
		return ret;} //super not initialized?
	oft = malloc(sizeof(inode*));
	int oft_size = read_itable( oft_buffer, oft, super.blockSize);
	if(DEBUG) printf("%d\n",63);
	free(oft_buffer);
	if (oft_size < 0){ //read failed?
		free(file);
		free(oft);
		return -1;}
	
	//verify the file is not open
	if(DEBUG) printf("%d\n",64);
	int i;
	for( i = 0; i < oft_size; i++)
		if( (*oft)[i].index == (*file).index){ //file is open
			free(file);
			free(*oft);
			free(oft);
			return -1;}
	if(DEBUG) printf("%d\n",65);
	free(*oft);
	free(oft);
	
	//get the file's parent's meta
	if(DEBUG) printf("%d\n",66);
	char* k;
	int lastSlash = 0;
	while((k = strchr(pathname + lastSlash + 1,'/'))!=NULL)
		lastSlash = k-pathname;
	char* parent_path = malloc(sizeof(char)*(lastSlash + 1));
	for(i = 0; i < lastSlash; i++)
		parent_path[i] = pathname[i];
	*(parent_path + 1) = '\0';
	if(DEBUG) printf("%d\n",67);
	inode* parent_meta = malloc(sizeof(inode));
	ret = parse(parent_path, parent_meta);
	free(parent_path);
	if(ret < 0) { //parent does not exist?\
			are we trying to delete the root?
		free(file);
		free(parent_meta);
		return ret;}
	
	//check other delete conditions
	if(DEBUG) printf("%d\n",68);
	if((*file).type = 1)//file is directory
		if((*file).size > 0){ //directories must be empty prior to deletion
			free(file);
			free(parent_meta);
			return -1;}
	
	//get the parent
	if(DEBUG) printf("%d\n",69);
	inode** parent; //parent inode table
	char* parent_buffer = malloc(sizeof(char)*super.blockSize);
	ret = get_block( (*parent_meta).index, parent_buffer);
	if(DEBUG) printf("%d\n",70);
	if (ret < 0) { //super not initialized?
		free(file);
		free(parent_meta);
		free(parent_buffer);
		return ret;}
	parent = malloc(sizeof(inode*));
	int parent_size = read_itable( parent_buffer, parent, super.blockSize);
	if(DEBUG) printf("%d\n",71);
	free(parent_buffer);
	if(DEBUG) printf("%d\n",72);
	if (parent_size < 0){ //read failed?
		free(file);
		free(parent_meta);
		free(parent);
		return -1;}
	
	//good, now delete
	if(DEBUG) printf("%d\n",73);
	for( i = 0; i < parent_size; i++)
		if( (*file).index == (*parent)[i].index){//found it
			if(DEBUG) printf("%d\n",74);
			while(i<parent_size){
				(*parent)[i] = (*parent)[i + 1];
				i++;}
			free(file);
			if(DEBUG) printf("%d\n",75);
			parent_buffer = malloc(sizeof(char)*super.blockSize);
			ret = write_itable( parent_buffer, *parent, super.blockSize);
			free(*parent);
			free(parent);
			if(ret < 0) { //write failed?
				free(parent_meta);
				free(parent_buffer);
				return ret;}
			if(DEBUG) printf("%d\n",76);
			ret = put_block( (*parent_meta).index, parent_buffer);
			free(parent_meta);
			free(parent_buffer);
			if(ret < 0) return ret;//put failed?
			//done
			bfree((*file).index, (*file).size/128 + 1);
			return 0;}
	//did not find (even thought pathname parse succeeded?
	if(DEBUG) printf("%d\n",77);
	free(file);
	free(*parent);
	free(parent);
	free(parent_meta);
	return -1;}
	
