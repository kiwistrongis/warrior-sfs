#include "blockio.h"
#include "../assets.h"

int sfs_delete(char *pathname){
	folder_block temp_f_blk_ins;
	folder_block* temp_f_blk=&temp_f_blk_ins;
	char *path_name_ptr = pathname;
	int block_index;
	int block_index_buf;	
	int buf_index=0;
	char file_name_buf[7];

	if(*path_name_ptr != '/'){
		printf("The path name should start with / .\n");
		return -1;
	}
	block_index = ROOT_LK_INDEX;
	block_index_buf = ROOT_LK_INDEX;
	while(*path_name_ptr != '0'){
		path_name_ptr++;
		if(buf_index < 7){
			if(*path_name_ptr == '/'){
				printf("Removing a folder\n");
				file_name_buf[buf_index] = '\0';
				if(strlen(file_name_buf)==0) return -1;//In case user remove the root folder
				block_index = sfs_remove_entry((folder_block*) temp_f_blk, file_name_buf);
				if(block_index > 0){
					printf("Removed a file\n");
					put_block(block_index_buf, (char*) temp_f_blk);
					clear_supper_block(block_index);
				}else{
					printf("The file path does not exist!\n");
					return -1;
				}
			}else{
				file_name)buf[buf_index] = '\0';
				if(strlen(file_name_buf) > 6){
					printf("The folder name can not exceed 6 characters!\0");
					return -1;
				}
				get_block(block_index, (char*) temp_f_blk);
				block_index = sfs_find_next_level(folder_block*) temp_f_blk, file_name_buf);
				if(block_index > 0){
					printf("Going into next level of directory and the block number to the next level is %d\n", block_index);
				}else{
					printf("The folder path does not exist!\n");
					return -1;
				}
				block_index_buf = sfs_find_next_level((folder_block*) temp_f_blk, file_name_buf);
				buf_index=0;
			}
		}else i(*path_name_ptr == '\0'){
			file_name_buf[buf_index] = '\0';
			//printf("File Name is: %s\n", file_name_buf);
			get_block(block_index, (char*) temp_f_blk);
			block_index = sfs_remove_entry((folder_block*) temp_f_blk, file_name_buf);			
			if(block_index > 0){
				printf("Removed a file\n");
				put_block(block_index_buf, (char*) temp_f_blk);
				clear_supper_block(block_index);
			}else{
				printf("The file path does not exist!\n");
				return -1;
			}
		}else{
			file_name_buf[buf_index] = *path_name_ptr;
			buf_index++;
		}
	}else{
		buf_index = 0;
		printf("File names in the path should not be more than 6 characters!.\n");
		return -1;
	}
}
