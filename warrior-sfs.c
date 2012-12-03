#include "warrior-sfs-lib.h"

int main(){
	int quit = 0;
	char* command = malloc(sizeof(char)*(20 + 1));
	char* buffer = malloc(sizeof(char)*(128 + 1));
	int ret;
	int* fd = malloc(sizeof(int));
	int* start = malloc(sizeof(int));
	int* length = malloc(sizeof(int));
	int* type = malloc(sizeof(int));
	int* size = malloc(sizeof(int));
	int* erase = malloc(sizeof(int));
	while(!quit){
		printf("$ ");
		scanf("%20s",command);
		if(!strcmp(command,"close")){
			scanf("%d",fd);
			ret = sfs_close(*fd);
			if( ret >= 0)
				printf("Closed\n");
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"create")){
			scanf("%s",buffer);
			scanf("%d",type);
			scanf("%d",size);
			ret = sfs_create( buffer, *type, *size);
			if( ret >= 0)
				printf("Created\n",ret);
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"dir")){
			scanf("%d", fd);
			ret = sfs_readdir( *fd, buffer);
			if( ret >= 0)
				printf("%s\n",buffer);
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"del")){
			scanf("%s",buffer);
			ret = sfs_delete( buffer);
			if( ret >= 0)
				printf("Deleted\n");
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"exit")) quit = 1;
		if(!strcmp(command,"init")){
			scanf("%d",erase);
			ret = sfs_initialize(*erase);
			if( ret >= 0)
				printf("Initialized\n");
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"open")){
			scanf("%s",buffer);
			ret = sfs_open(buffer);
			if( ret >= 0)
				printf("Opened with fd: %d\n",ret);
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"read")){
			scanf("%d",fd);
			scanf("%d",start);
			scanf("%d",length);
			ret = sfs_read( *fd, *start, *length, buffer);
			if( ret >= 0)
				printf("%s\n",buffer);
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"size")){
			scanf("%s",buffer);
			ret = sfs_getsize(buffer);
			if( ret >= 0)
				printf("%d\n",ret);
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"type")){
			scanf("%s",buffer);
			ret = sfs_gettype(buffer);
			if( ret >= 0)
				printf("%d\n",ret);
			else
				printf("Error: %d\n",ret);}
		if(!strcmp(command,"write"));}
	free(command);
	free(buffer);
	free(fd);
	free(start);
	free(length);
	free(type);
	free(size);
	free(erase);
	return 0;}
