#universals
default: all
clean: tools/cleandir \
		clean-extras
	tools/cleandir
	tools/cleandir assets
	tools/cleandir functions
	tools/cleandir tests
	tools/cleandir tools
	rm -f -r documentation
check: all clean
freshen: clean all
jdoc:	javadoc -d documentation \
		-sourcepath . \
		*.ja*
cdoc: doxyfile codefiles
	doxygen
	
#all
all: assets functions locals
locals: \
		warrior-sfs \
		warrior-sfs.o \
		warrior-sfs-lib.a
assets: \
		assets/blockio.o \
		assets/free_block_table.o \
		assets/inode.o \
		assets/parsing.o \
		assets/superblock.o \
		assets/utility.o
functions: \
		functions/close_file.o \
		functions/create_file.o \
		functions/delete_file.o \
		functions/get_size.o \
		functions/get_type.o \
		functions/initialize.o \
		functions/open_file.o \
		functions/read_dir.o \
		functions/read_file.o \
		functions/write_file.o
tests-major: warrior-sfs
tests-minor: \
		tests/intest.out \
		tests/ittest.out \
		tests/sbtest.out \
		tests/scantest.out
experiments: \
		tests/casting.out\
		tests/shift.out
clean-extras:
	rm -f warrior-sfs
test: tests-major
	./warrior-sfs
test-minor: tests-minor
	tests/intest.out
	tests/ittest.out
	tests/sbtest.out
	tests/scantest.out
test-all: test-minor test

#locals
warrior-sfs: warrior-sfs.o \
		warrior-sfs-lib.a
	gcc -o warrior-sfs \
		warrior-sfs.o \
		warrior-sfs-lib.a

warrior-sfs.o: warrior-sfs.c \
		warrior-sfs-lib.h
	gcc -c -g warrior-sfs.c -o warrior-sfs.o

warrior-sfs-lib.a: \
		warrior-sfs-lib.h \
		assets \
		functions
	ar rc warrior-sfs-lib.a \
		assets/blockio.o \
		assets/free_block_table.o \
		assets/inode.o \
		assets/parsing.o \
		assets/superblock.o \
		assets/utility.o \
		functions/close_file.o \
		functions/create_file.o \
		functions/delete_file.o \
		functions/get_size.o \
		functions/get_type.o \
		functions/initialize.o \
		functions/open_file.o \
		functions/read_dir.o \
		functions/read_file.o \
		functions/write_file.o
	ranlib warrior-sfs-lib.a

warrior-sfs-lib.h: assets.h
assets.h: \
	assets/blockio.h \
	assets/free_block_table.h \
	assets/open_file_table.h \
	assets/parsing.h \
	assets/superblock.h \
	assets/utility.h

#assets
assets/blockio.o: assets/blockio.h assets/blockio.c \
		assets.h
	gcc -c -g assets/blockio.c -o assets/blockio.o
	
assets/free_block_table.o: assets/free_block_table.c \
		assets/free_block_table.h \
		assets/blockio.h \
		assets/superblock.h \
		assets.h
	gcc -c -g assets/free_block_table.c -o assets/free_block_table.o
	
assets/utility.o: assets/utility.c \
		assets.h
	gcc -c -g assets/utility.c -o assets/utility.o
	
assets/inode.o: assets/inode.c assets/inode.h \
		assets.h
	gcc -c -g assets/inode.c -o assets/inode.o
	
assets/parsing.o: assets/parsing.c assets/parsing.h \
		assets/inode.h \
		assets/superblock.h \
		assets.h
	gcc -c -g assets/parsing.c -o assets/parsing.o
	
assets/superblock.o: assets/superblock.c assets/superblock.h \
		assets.h \
		assets/blockio.h \
		assets/inode.h \
		
	gcc -c -g assets/superblock.c -o assets/superblock.o

#functions
functions/close_file.o: functions/close_file.c \
		warrior-sfs-lib.h
	gcc -c -g functions/close_file.c -o functions/close_file.o
	
functions/create_file.o: functions/create_file.c \
		warrior-sfs-lib.h
	gcc -c -g functions/create_file.c -o functions/create_file.o
	
functions/delete_file.o: functions/delete_file.c \
		warrior-sfs-lib.h
	gcc -c -g functions/delete_file.c -o functions/delete_file.o
	
functions/get_size.o: functions/get_size.c \
		warrior-sfs-lib.h
	gcc -c -g functions/get_size.c -o functions/get_size.o
	
functions/get_type.o: functions/get_type.c \
		warrior-sfs-lib.h
	gcc -c -g functions/get_type.c -o functions/get_type.o
	
functions/initialize.o: functions/initialize.c \
		warrior-sfs-lib.h
	gcc -c -g functions/initialize.c -o functions/initialize.o
	
functions/open_file.o: functions/open_file.c \
		warrior-sfs-lib.h
	gcc -c -g functions/open_file.c -o functions/open_file.o
	
functions/read_dir.o: functions/read_dir.c \
		warrior-sfs-lib.h
	gcc -c -g functions/read_dir.c -o functions/read_dir.o
	
functions/read_file.o: functions/read_file.c \
		warrior-sfs-lib.h
	gcc -c -g functions/read_file.c -o functions/read_file.o
	
functions/write_file.o: functions/write_file.c \
		warrior-sfs-lib.h
	gcc -c -g functions/write_file.c -o functions/write_file.o

#major tests
tests/sfstest.o: tests/sfstest.c \
		warrior-sfs-lib.h
	gcc -c -g tests/sfstest.c -o tests/sfstest.o

tests/sfstest.out: tests/sfstest.o \
		warrior-sfs-lib.a
	gcc -o tests/sfstest.out tests/sfstest.o \
		warrior-sfs-lib.a

#minor tests
tests/casting.out: tests/casting.c
	gcc tests/casting.c -o tests/casting.out

tests/intest.o: tests/intest.c \
		assets.h \
		assets/inode.h
	gcc -c -g tests/intest.c -o tests/intest.o

tests/intest.out: tests/intest.o \
		assets/utility.o \
		assets/inode.o
	gcc -o tests/intest.out tests/intest.o \
		assets/utility.o \
		assets/inode.o

tests/ittest.o: tests/ittest.c \
		assets.h \
		assets/inode.h
	gcc -c -g tests/ittest.c -o tests/ittest.o

tests/ittest.out: tests/ittest.o \
		assets/utility.o \
		assets/inode.o
	gcc -o tests/ittest.out tests/ittest.o \
		assets/utility.o \
		assets/inode.o

tests/shift.out: tests/shift.c
	gcc tests/shift.c -o tests/shift.out

tests/sbtest.o: tests/sbtest.c \
		assets.h \
		assets/superblock.h
	gcc -c -g tests/sbtest.c -o tests/sbtest.o

tests/sbtest.out: tests/sbtest.o \
		assets/blockio.o \
		assets/utility.o \
		assets/inode.o \
		assets/superblock.o
	gcc -o tests/sbtest.out tests/sbtest.o \
		assets/blockio.o \
		assets/utility.o \
		assets/inode.o \
		assets/superblock.o

tests/scantest.out: tests/scantest.c
	gcc -o tests/scantest.out tests/scantest.c

#codefiles
codefiles: \
		codefiles-assets \
		codefiles-functions \
		codefiles-locals \
		codefiles-tests

codefiles-assets: \
		assets/blockio.c \
		assets/blockio.h \
		assets/free_block_table.c \
		assets/free_block_table.h \
		assets/utility.c \
		assets/inode.c \
		assets/inode.h \
		assets/superblock.c \
		assets/superblock.h \

codefiles-functions: \
		functions/close_file.c \
		functions/create_file.c \
		functions/delete_file.c \
		functions/get_size.c \
		functions/get_type.c \
		functions/initialize.c \
		functions/open_file.c \
		functions/read_dir.c \
		functions/read_file.c \
		functions/write_file.c

codefiles-locals: \
		assets.h \
		warrior-sfs.c \
		warrior-sfs-lib.h

codefiles-tests: \
		tests/casting.c \
		tests/intest.c \
		tests/ittest.c \
		tests/sbtest.c \
		tests/sfstest.c \
		tests/shift.c
