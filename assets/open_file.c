#include "blockio.h"
#include "../assets.h"

int sfs_open(char *pathname){
	  int i,j;
    char temp_f_blk[128];
    data_blcok * temp_d_blk;
    char *path_name_ptr = pathname;
    char file_name_buf[7];
    int buf_index = 0;
    int block_index;
    //printf("The input Path name is :%s\n", pathname);
    //printf("First Char is: %d\n", *path_name_ptr);
    if (*path_name_ptr != '/') {
        printf("The path name should start with / .\n");
        return -1;
    }
    if (*(path_name_ptr + 1) == '\0') {
        //root directory
        if (get_block(ROOT_LK_INDEX, open_i_blcok[number_file_open].block_content) != 0) return -1;
        for (j = 0; j < MAX_OPEN_FILES; j++) {
            if (!open_i_blcok[j].valid) break;
        }
        if (j == MAX_OPEN_FILES) return -1;
        open_i_blcok[j].block_index = ROOT_LK_INDEX;
        open_i_blcok[j].file_ptr = 0;
        open_i_blcok[j].type = (open_i_blcok[number_file_open].block_content)[0];
        printf("%d\n", open_i_blcok[j].type);
        open_i_blcok[j].valid = 1;
        //if (temp_d_blk)
        return j;
    }
    block_index = ROOT_LK_INDEX;
    //path_name_ptr++;
    while (*path_name_ptr != '\0') {
        path_name_ptr++;
        if (buf_index < 7) {
            if (*path_name_ptr == '/') {
                if (*(path_name_ptr + 1) == '\0') {
                    printf("You need to specify a file name not a folder name at the end\n");
                    return -1;
                }
                //Just found a directory
                file_name_buf[buf_index] = '\0';

                //if(get_block(block_index, (char*) temp_f_blk)!=0) return -1;
                get_block(block_index, temp_f_blk);
                block_index = sfs_find_next_level((floder_blcok*) temp_f_blk, file_name_buf);

                if (block_index > 0) {
                } else {
                    printf("Invalid path name!!\n");
                    return -1;
                }
                buf_index = 0;
            } else if (*path_name_ptr == '\0') {
                file_name_buf[buf_index] = '\0';
                if (get_block(block_index, temp_f_blk)!=0) return -1 ;
                block_index = sfs_find_next_level((floder_blcok*) temp_f_blk, file_name_buf);        
                if (block_index > 0) {
                    printf("The spcified file exists\n");

                    if (number_file_open == MAX_OPEN_FILES) {
                        printf("Can not open more files on the system\n");
                        return -1;
                    } else {
                       
                        //Has the file and the file can be open, return the discripter
                        number_file_open++;
                        open_file_list[number_file_open] = block_index;
                        if(get_block(block_index, open_i_blcok[number_file_open].block_content)<0){
                            return -1;
                        }
                        printf("size of the file is %d", ((data_blcok*)(open_i_blcok[number_file_open].block_content))->file_size);
                        for (j=0;j<MAX_OPEN_FILES;j++){
                            if (!open_i_blcok[j].valid) break;
                        }
                        if (j==MAX_OPEN_FILES) return -1;
                        open_i_blcok[j].block_index=block_index;
                        open_i_blcok[j].file_ptr=0;
                        open_i_blcok[j].type=(open_i_blcok[number_file_open].block_content)[0];
                        printf("%d\n",open_i_blcok[j].type);
                        open_i_blcok[j].valid=1;
                        //if (temp_d_blk)
                        return j;
                    }
                } else {
                    printf("Sorry, the file you specified does not exist!");
                    return -1;
                }
                buf_index = 0;
            } else {
                file_name_buf[buf_index] = *path_name_ptr;
                buf_index++;
            }
        } else {
            buf_index = 0;
            printf("File names in the path should not be more than 6 chars!.\n");
            return -1;
        }
    }
}
