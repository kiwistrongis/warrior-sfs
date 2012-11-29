#include "../assets.h"

/* This is the maximum number of bytes that can be read from or written to a file with a single file system call using this program.  Since files are limited to 512 bytes length, this should be sufficient. */
/* the format definition is necessary because macro substitutions do not take place within quoted strings */
#define MAX_IO_LENGTH   1024       /* I CHANGED IT FROM 512--->1024 */
#define IO_BUF_FORMAT   "%512s"

/* This is the maximum length of input strings (e.g., file names) read from
the standard input.  This should be large enough for most purposes. */
/* the format definition is necessary because macro substitutions do not take place within quoted strings */
#define MAX_INPUT_LENGTH  512
#define INPUT_BUF_FORMAT  "%1024s"

/**
 * Global data structures
 */

// buffer to hold commands read from standard input
char* command_buffer;
// buffer to hold data going to/from the disk
char* io_buffer;
// the following is used to hold string input parameters, such as file names
char* data_buffer_1;
// the following are used to hold integer input parameters
int p1,p2,p3;

/**
 * main test routine
 */
main(){
	int i;
	int retval;  /* used to hold return values of file system calls */
	command_buffer = malloc (sizeof(char)*(MAX_INPUT_LENGTH+1));
	io_buffer = malloc (sizeof(char)*(MAX_IO_LENGTH+1));
	data_buffer_1 = malloc (sizeof(char)*(MAX_INPUT_LENGTH));

	/* do forever:
	1) print a list of available commands
	2) read a command
	3) read arguments for the command
	4) perform the requested operation
	5) display the results of the operation
*/
	while(1) {
		/* print a list of available commands */
		printf("\n");
		printf("o: open a file\n");
		printf("r: read from a file\n");
		printf("w: write to a file\n");
		printf("R: read from a directory\n");
		printf("c: close a file\n");
		printf("m: create (make) a new file\n");
		printf("d: delete a file\n");
		printf("s: get the size of a file\n");
		printf("t: get the type of a file\n");
		printf("i: initialize the file system\n");
		printf("q: quit - exit this program\n");
		
		/* read in the next command */
		printf("\nCommand? ");
		if (gets(command_buffer) == NULL) break;
		
		/* determine which command was requested */
		switch(command_buffer[0]) {
		case 'o':
			/* Open a file */
			printf("Enter full path name of file to open: ");
			scanf(INPUT_BUF_FORMAT,data_buffer_1);
			retval = sfs_open(data_buffer_1);
			if (retval >= 0)
				printf("Open succeeded.  File Descriptor number is %d\n",retval);
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 'r':
			/* Read from a file */
			printf("Enter file descriptor number: ");
			scanf("%d",&p1);
			printf("Enter read start location: ");
			scanf("%d",&p2);
			printf("Enter number of bytes to read: ");
			scanf("%d",&p3);
			retval = sfs_read(p1,p2,p3,io_buffer);
			if (retval > 0) {
				printf("Read succeeded.\n");
				printf("The following data was read (only printable ASCII will display)\n");
				for(i=0;i<p3;i++)
					putchar(io_buffer[i]);
				printf("\n");}
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 'w':
			/* Write to a file */

			printf("Enter file descriptor number: ");
			scanf("%d",&p1);
			printf("Enter write start location: ");
			scanf("%d",&p2);
			printf("Enter number of bytes to write: ");
			scanf("%d",&p3);
			printf("This program allows only non-white-space, printable ASCII characters to be written to a file.\n");
			printf("Enter %d characters to be written: ",p3);
			scanf(IO_BUF_FORMAT,io_buffer);
			retval = sfs_write(p1,p2,p3,io_buffer);
			if (retval > 0) {
				printf("Write succeeded.\n");
				printf("Wrote %s to the disk\n",io_buffer);}
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 'R':
			/* Read from a directory */
			printf("Enter file descriptor number: ");
			scanf("%d",&p1);
			retval = sfs_readdir(p1,io_buffer);
			if (retval > 0) {
				printf("sfs_readdir succeeded.\n");
				printf("Directory entry is: %s\n",io_buffer);}
			else if (retval == 0) {
				printf("sfs_readdir succeeded.\n");
				printf("No more entries in this directory\n");}
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 'c':
			/* Close a file */
			printf("Enter file descriptor number: ");
			scanf("%d",&p1);
			retval = sfs_close(p1);
			if (retval > 0)
				printf("sfs_close succeeded.\n");
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 'm':
			/* Create a new file */
			printf("Enter full path name of new file: ");
			scanf(INPUT_BUF_FORMAT,data_buffer_1);
			printf("Enter 0 for regular file, 1 for directory: ");
			scanf("%d",&p1);
			retval = sfs_create(data_buffer_1,p1);
			if (retval > 0)
				printf("sfs_create succeeded.\n");
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 'd':
			/* Delete a file */
			printf("Enter full path name of file to delete: ");
			scanf(INPUT_BUF_FORMAT,data_buffer_1);
			retval = sfs_delete(data_buffer_1);
			if (retval > 0)
				printf("sfs_delete succeeded.\n");
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 's':
			/* Get the size of a file */
			printf("Enter full path name of file: ");
			scanf(INPUT_BUF_FORMAT,data_buffer_1);
			retval = sfs_getsize(data_buffer_1);
			if (retval >= 0) {
				printf("sfs_getsize succeeded.\n");
				printf("size = %d\n",retval);}
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 't':
			/* Get the type of a file */
			printf("Enter full path name of file: ");
			scanf(INPUT_BUF_FORMAT,data_buffer_1);
			retval = sfs_gettype(data_buffer_1);
			if (retval >= 0) {
				printf("sfs_gettype succeeded.\n");
				if (retval == 0)
					printf("file type is REGULAR\n");
				else if (retval == 1)
					printf("file type is DIRECTORY\n");
				else
					printf("file has unknown type %d\n",retval);}
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 'i':
			/* Initialize the file system */
			printf("Enter 1 to erase disk while initializing, 0 otherwise: ");
			scanf("%d",&p1);
			retval = sfs_initialize(p1);
			if (retval > 0)
				printf("sfs_initialize succeeded.\n");
			else
				printf("Error.  Return value was %d\n",retval);
			break;
		case 'q':
			/* Quit this program */
			break;
		default:
			printf("Unknown command: %s\n",command_buffer);
			break;}
		if (command_buffer[0] == 'q'){
			free(command_buffer);
			free(io_buffer);
			free(data_buffer_1);
			break;}
		/* cleanup the newline that remains after reading command parameter(s) */
		gets(command_buffer);
	}
	return 0;
}
