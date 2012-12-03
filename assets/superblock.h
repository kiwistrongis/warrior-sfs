typedef struct {
	int blockSize;//in bytes
	int blockCount;//number of blocks on disk
	int super_loc;//blocknum of super block
	int openFileTable_loc;//blocknum of open file table
	int freeBlockTable_loc;//blocknum of free block table
	inode root;//root directory's inode
} Superblock;

Superblock super;

//this code only works with all superblock fields <=(1<<14) -1 (16383)
//see tests/casting.c and .out for experimental work
int init_superblock();
int put_superblock();
int get_superblock();
