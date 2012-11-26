#include "blockio.h"
#include "../assets.h"

int sfs_create(char *pathname, int type){
	folder_block temp_f_blk_ins;
	folder_block* temp_f_blk=&temp_f_blk_ins;	

	int i;
	data_block * temp_d_blk;
	char *path_name_ptr = pathname;
	char file_name_buf[7];
	int buf_index = 0;
	int block_index;
	int blok_index_buf;
	//printf("The input Path name is :%s\n", pathname);	
	//printf("First character is: %d\n", *path_name_ptr);
	if(*path_name_ptr != '/'){
		printf("The path name should start with /.\n");
		return -1;
	}

	block_index = ROOT_LK_INDEX;
	block_index_buf = ROOT_LK_INDEX;
	//path_name_ptr++;	
	while(*paht_name_ptr !='\0'){
		path_name_ptr++;
		if(buf_index <7){
			if(*path_name_ptr == '/'){
				if(*(path_name_ptr +1) == '\0');{
					printf("You need to specifiy a file name not a folder name at the end\n");
					return -1;
				}
				//Just found a directory
				file_name_buf[buf_index] = '\0';
				//printf("Directory Name is: %s\n", file_name_buf);
				if(strlen(file_name_buf) > 6){
					printf("The folder name can not exceed 6 characters!\0");
					return -1;
				}
				get_block(block_index, (char*) temp_f_blk);
				block_index = sfs_find_next_level((folder_block*) temp_f_blk, file)name_buf);
				if(block_index > 0){
					printf("Going into next level of directory and the block number to the enxt level is %d\n", block_index);
				}else{
					printf("The folder path does not exist, is being created.\n");
				//Here it is checking all the contents in the folder to find an empty slot
				for(i=1; i<NUM_CONTENT_IN_FOLDER;i++){
					if(temp_f_blk->dest_list[i] ==0){
						strcpy(temp_f_blk->name_list[i], file_name_buf);
						/*waiting for the folder creating code here*/
						printf("Placing it in location: %d\n", find_first_empty_block());
						temp_f_blk->dest_list[i] = find_first_empty_block();
						if(create_folder_block(temp_f_blk->dest_list[i], file_name_buf)==0){
							put_block(block_index_buf, (char*) temp_f_blk);
						}
						break;
					}
				}
				if(i==NUM_CONTENT_IN_FOLDER){
					printf("The folder is full, couldn't create more folders within it.\n");
					return -1;
				}
			}
			block_index_buf = sfs_find_next_level((folder)block*) temp_f_blk, file_name_buf);
			buf_index = 0;
		}else if)*path_name_ptr == '\0'){
			file_name_buf[buf_index] = '\0';
			//printf("File Name is: %s\n", file_name_buf);
			get_block(block_index, (char*) temp_f_blk);
			block_index = sfs_find_next_level((folder_block*) temp_f_blk, file_name_buf);
			if(block_index >0){
				printf("The file already exists!\n");
				return -1;
			}else{
				for(i=1;i<NUM_CONTENT_IN_FOLDER;i++){
					if(temp_f_blk->dest_list[i] ==0){
						//printf("size: %s\n", sizeof(temp_f_blk->name_list[i]));
						strcpy(temp_f_blk->name_list[i], file_name_buf);
						printf("Placing it at the location: %d\n", find_first_empty_block());
						temp_f_blk->dest_list[i] = find_first_empty_block();
						if(!type)
							if(create_file_block(temp_f_blk->dest_list[i], file_name_buf)==0){
								put_block(block_index_buf, (char*) temp_f_blk);
								return 1;
							}
							else return 0;
						else
							if(create_folder_block(temp_f_blk->dest_list[i],file_name_buf)==0){
								put_block(block_index_buf, (char*) temp_f_blk);
								return 1;
							}
							else return 0;
						break;
					}
				}
				if(i==NUM_CONTENT_IN_FOLDER){
					printf("The folder is full, couldn't create more folders under it.\n");
					return -1;
				}
			}
			buf_index = 0;
			break;
		}else{
			file_name_buf[buf_index] = *path_name_ptr;
			buf_index++;
		}
	}else{
		buf_index = 0;
		printf("File names in the path should not be more than 6 characters!\n");
		return -1;
	}
}
}
