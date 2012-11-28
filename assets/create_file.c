#include "blockio.h";
#include "../assets.h";
	
int sfs_create(char *pathname, int type){
	int i;
	char *path_name_ptr = pathname;
	char file_name_buf[7];

	//get the inode table
	char *s[directory_inode.size];
	s = get_block(directory);	
	*(s+directory_inode.size) = '\0';
	inode *itable;

	//parse the pathname?

	if(*path_name_ptr != '/'){//invalid pathname
			printf("Need to start pathname with /\n");
			return -1;}
	while(*path_name_ptr != '\0'){
		path_name_ptr++;	
		//filename less than or equal to 6 chars
		if(*path_name_ptr.len <=7){
			//check if file already exists
			if((parse(/*filename*/, *path_name_ptr)>=0){
				printf("File name already exists\n");
				return -1;
			}else{
				//create file
				/*create file code*/
				if(type == 0){//create regular file
					/*create*/
				}else if(type == 1){//create directory file
					if((parse())>=0){
						/*create*/}//verify pathname components
				else{printf("File type not recognized, 0 or 1 only");}}}
	}
