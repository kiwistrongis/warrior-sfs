#include "../warrior-sfs-lib.h"

int sfs_initialize(int erase){
	int ret;
	if(DEBUG) printf("%d\n",26);
	if(erase > 0){
		char * zero_block;
		zero_block = calloc(128, sizeof(char));
		int i;
		for(i = 0; i < 512; i++)
			put_block(i,zero_block);
		if(DEBUG) printf("%d\n",27);
		
		ret = init_superblock();
		bfree(0,512);
		if(ret < 0)
			return ret;
		set_used(super.super_loc);
		set_used(super.openFileTable_loc);
		set_used(super.freeBlockTable_loc);
		set_used(super.root.index);}
	if(DEBUG) printf("%d\n",28);
	ret = get_superblock();
	if(ret < 0)
		return ret;
	return 0;
}
