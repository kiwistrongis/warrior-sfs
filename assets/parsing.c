#include "parsing.h"


int parse(char* s, inode* dest){
	int length = strlen(s);
	free (dest);
	if (length <=0)
		return -1;
	else if ( length ==1)
		if(s[0]=='/'){
			dest = (inode*)&(super.root);
			return 0;}
		else
			return -1;
	else {
		return parse_it(s+1,dest,super.root);}}

int parse_it(char* s, inode* dest, inode i){
	char* rem = strchr(s,'/');
	if(rem==NULL);//we are on last token
		//find token in i's itable
	int token_length = rem-s;
	if(token_length=0)//empty token
		return -1;
	else if(token_length>5)//overweight token
		return -1;
	else {
		char* block = malloc(sizeof(char)*128);
		int ret = get_block(i.index,block);
		if (ret<0){
			free(block);
			return ret;}
		char* itable_buffer = malloc(sizeof(char)*i.size);
		strncpy(itable_buffer,block,i.size);
		*(itable_buffer+i.size) = '\0';
		inode* itable; 
		
		int rem_length = strlen(rem);
		if(rem_length>1)
