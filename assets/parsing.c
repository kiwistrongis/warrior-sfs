#include "../assets.h"

int parse(char* s, inode* dest){
	if(DEBUG) printf("%d\n",80);
	int length = strlen(s);
	free (dest);
	if (length <=0)
		return -1;
	else if ( length ==1)
		if(s[0]=='/'){
			*dest = super.root;
			return 0;}
		else
			return -1;
	else {
		if(DEBUG) printf("%d\n",81);
		return parse_it( s + 1 , dest,super.root);}}

int parse_it(char* s, inode* dest, inode parent){
	if(DEBUG) printf("%d\n",82);
	char* rem = strchr(s,'/');
	if(rem==NULL);//we are on last token and inode must be 
	int token_length = rem - s;
	if(token_length=0)//empty token
		return -1;
	else if(token_length > 5)//overweight token
		return -1;
	
	if(DEBUG) printf("%d\n",83);
	char* token = calloc((1+token_length),sizeof(char));
	int i;
	for( i = 0; i < token_length; i++)
		token[i] = s[i];
	token[token_length] = '\0';
	char* block = malloc(sizeof(char)*128);
	int ret = get_block(parent.index,block);
	if(DEBUG) printf("%d\n",84);
	if (ret<0){
		free(block);
		return ret;}
	inode** itable;
	itable = malloc(sizeof(inode*));
	ret = read_itable( block, itable,128);
	inode* looking = *itable;
	if(DEBUG) printf("%d\n",85);
	while (strlen((*looking).name)>0){
		if(strcmp((*looking).name,token)==0)//we found it!
			if(strlen(rem)>1){ //we have have more tokens to parse
				if(DEBUG) printf("%d\n",86);
				free(token);
				free(block);
				ret = (*looking).type?
					parse_it(rem+1, dest, *looking):
					-1;
				free(*itable);
				free(itable);
				if(DEBUG) printf("%d\n",87);
				return ret;}
			else{ //we are done!
				if(DEBUG) printf("%d\n",88);
				*dest = *looking;
				free(token);
				free(block);
				free(*itable);
				free(itable);
				return 0;}
		looking+=sizeof(inode);}
	//token not found!
	if(DEBUG) printf("%d\n",89);
	free(token);
	free(block);
	free(*itable);
	free(itable);
	if(DEBUG) printf("%d\n",90);
	return -1;}
	
	
	
	
	
	
