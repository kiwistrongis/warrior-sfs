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
		return parse_it( s + 1 , dest,super.root);}}

int parse_it(char* s, inode* dest, inode parent){
	char* rem = strchr(s,'/');
	if(rem==NULL);//we are on last token and inode must be 
	int token_length = rem - s;
	if(token_length=0)//empty token
		return -1;
	else if(token_length > 5)//overweight token
		return -1;
	else {
		char* token = calloc((1+token_length),sizeof(char));
		int i;
		for( i = 0; i < token_length; i++)
			token[i] = s[i];
		token[token_length] = '\0';
		char* block = malloc(sizeof(char)*128);
		int ret = get_block(parent.index,block);
		if (ret<0){
			free(block);
			return ret;}
		inode* itable;
		ret = read_itable( block, (inode**)&itable,128);
		inode* looking = itable;
		while (strlen((*looking).name)>0){
			if(strcmp((*looking).name,token)==0)//we found it!
				if(strlen(rem)>1){ //we have have more tokens to parse
					free(token);
					free(block);
					ret = parse_it(rem+1, dest, *looking);
					free(itable);
					return ret;}
				else{ //we are done!
					*dest = *looking;
					free(token);
					free(block);
					free(itable);
					return 0;}}
		//token not found!
		free(token);
		free(block);
		free(itable);
		return -1;}}
		
		
		
		
		
		
