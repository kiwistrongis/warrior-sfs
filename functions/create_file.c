#include "../warrior-sfs-lib.h"
	
int sfs_create(char *pathname, int type, int size){
	inode* file = malloc(sizeof(inode));
	(*file).index = -1;
	(*file).type = type;
	(*file).size = size;
	(*file).name = NULL;
	
	//get the file's parent's meta
	char* k;
	int lastSlash = 0;
	while((k = strchr(pathname + lastSlash + 1,'/'))!=NULL)
		lastSlash = k-pathname;
	char* parent_path = malloc(sizeof(char)*(lastSlash + 1));
	int i;
	for(i = 0; i < lastSlash; i++)
		parent_path[i] = pathname[i];
	*(parent_path + 1) = '\0';
	inode* parent_meta = malloc(sizeof(inode));
	int ret = parse(parent_path, parent_meta);
	free(parent_path);
	if(ret < 0) { //parent does not exist
		free(file);
		free(parent_meta);
		return ret;}
	
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
	
	//get name field
	(*file).name = pathname + lastSlash + 1;
	
	//get block allocation
	(*file).index = balloc(size);
	
	//add to parent
	parent_size++;
	*parent = realloc(*parent, sizeof(inode)*(parent_size + 1));
	(*parent)[parent_size] = (*parent)[parent_size - 1];
	(*parent)[parent_size - 1] = *file;
	
	//put parent
	parent_buffer = malloc(sizeof(char)*super.blockSize);
	ret = write_itable( parent_buffer, *parent, super.blockSize);
	free((*file).name);
	free(file);
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
	return 0;}
