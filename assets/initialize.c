#include "blockio.h"
#include "super_block.h"
#include "../assets.h"

int sfs_initialize(int erase){
	int i,j,k;
    folder_blcok root_blk;
    char temp_block[128];
    printf("Initializing the file system with the option 0\n");
    number_file_open = 0;

    /*Initializing the open_i_blcok*/
    for (k=0;k<MAX_OPEN_FILES;k++){
        open_i_blcok[k].valid=0;
        open_i_blcok[k].block_index=0;
    }

    switch (erase) {
        case 0:
            printf("Initializing the file system with the option 0\n");
            printf("Trying to load the file structure.\n");
            get_block(0, SB.super_block_0);
            get_block(1, SB.super_block_1);
            //printf("1st byte %x\n", SB.super_block_0[0]);

            return 1;
        case 1:
            printf("Initializing the file system with the option 1\n");
            printf("Trying to recreate the file system.\n");
            for (i = 0; i < BLKSIZE; i++) {
                if (i == 0) {
                    SB.super_block_0[i] = 3;
                    printf("1st byte %x\n", SB.super_block_0[0]);
                } else if(i == 1){
                    SB.super_block_0[i] = 2;
                }
                else SB.super_block_0[i] = 0;
                SB.super_block_1[i] = 0;
            }
            root_blk.type = 1;
            root_blk.valid = 1;
            //strcpy(&(root_blk.name_list[0][0]), "test");
            for (i = 0; i < NUM_CONTENT_IN_FOLDER; i++) {
                root_blk.dest_list[i] = 0;
                root_blk.name_list[i][0]='\0';
            }
            root_blk.dest_list[0] = ROOT_LK_INDEX + 1;

            put_block(0, SB.super_block_0);
            put_block(1, SB.super_block_1);


            put_block(ROOT_LK_INDEX, (char*) & root_blk);
            for (i=ROOT_LK_INDEX+1;i<NUMBLKS;i++){
                get_block(i, temp_block);
                for (j=0;j<BLKSIZE;j++){
                    temp_block[j]=0;
                }
                put_block(i, temp_block);
            }
            sfs_list_next_level(&root_blk);
            return 1;
    }

}