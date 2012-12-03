#define index_pos 0
#define size_pos 1
#define type_pos 2
#define length_pos 3
#define name_pos 4 //name must always be last

typedef struct{
	int index;//index of file's first block on disk
	int size;//size in bytes
	int type;//0 if directory, 1 otherwise
	char* name;//name of file
} inode;

int size_in_blocks(inode i);
char* write_inode(inode i);
inode read_inode(char* s);
int write_itable(char* result, inode* t, int result_size_alloc);
int read_itable(char* s, inode** t, int s_size);
