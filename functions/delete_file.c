#include "../warrior-sfs-lib.h"

int sfs_delete(char* pathname){
	//get the file's meta
	inode* file = malloc(sizeof(inode));
	int ret = parse(pathname, file);
	if (ret < 0) {//parse failed, file does not exist?
		free(file);
		return ret;}
	
	//get open file table
	inode** oft; //open file table
	char* oft_buffer = malloc(sizeof(char)*super.blockSize);
	ret = get_block( super.openFileTable_loc, oft_buffer);
	if (ret < 0) {
		free(file);
		free(oft_buffer);
		return ret;} //super not initialized?
	oft = malloc(sizeof(inode*));
	int oft_size = read_itable( oft_buffer, oft, super.blockSize);
	free(oft_buffer);
	if (oft_size < 0){ //read failed?
		free(file);
		free(oft);
		return -1;}
	
	//verify the file is not open
	int i;
	for( i = 0; i < oft_size; i++)
		if( (*oft)[i].index == (*file).index){ //file is open
			free(file);
			free(*oft);
			free(oft);
			return -1;}
	free(*oft);
	free(oft);
	
	//get the file's parent's meta
	char* k;
	int lastSlash = 0;
	while((k = strchr(pathname + lastSlash + 1,'/'))!=NULL)
		lastSlash = k-pathname;
	char* parent_path = malloc(sizeof(char)*(lastSlash + 1));
	for(i = 0; i < lastSlash; i++)
		parent_path[i] = pathname[i];
	*(parent_path + 1) = '\0';
	inode* parent_meta = malloc(sizeof(inode));
	ret = parse(parent_path, parent_meta);
	free(parent_path);
	if(ret < 0) { //parent does not exist? O_o makes no sense, wont happen
		free(file);
		free(parent_meta);
		return ret;}
	
	//check other delete conditions
	if((*file).type = 1)//file is directory
		if((*file).size > 0){ //directories must be empty prior to deletion
			free(file);
			free(parent_meta);
			return -1;}
	
	//get the parent
	inode** parent; //parent inode table
	char* parent_buffer = malloc(sizeof(char)*super.blockSize);
	ret = get_block( (*parent_meta).index, parent_buffer);
	if (ret < 0) { //super not initialized?
		free(file);
		free(parent_meta);
		free(parent_buffer);
		return ret;}
	parent = malloc(sizeof(inode*));
	int parent_size = read_itable( parent_buffer, parent, super.blockSize);
	free(parent_buffer);
	if (parent_size < 0){ //read failed?
		free(file);
		free(parent_meta);
		free(parent);
		return -1;}
	
	//good, now delete
	for( i = 0; i < parent_size; i++)
		if( (*file).index == (*parent)[i].index){//found it
			while(i<parent_size){
				(*parent)[i] = (*parent)[i + 1];
				i++;}
			free(file);
			parent_buffer = malloc(sizeof(char)*super.blockSize);
			ret = write_itable( parent_buffer, *parent, super.blockSize);
			free(*parent);
			free(parent);
			if(ret < 0) { //write failed?
				free(parent_meta);
				free(parent_buffer);
				return ret;}
			ret = put_block( (*parent_meta).index, parent_buffer);
			free(parent_meta);
			free(parent_buffer);
			if(ret < 0) return ret;//put failed?
			//done
			bfree((*file).index, (*file).size/128 + 1);
			return 0;}
	//did not find (even thought pathname parse succeeded?
	free(file);
	free(*parent);
	free(parent);
	free(parent_meta);
	return -1;}
	
