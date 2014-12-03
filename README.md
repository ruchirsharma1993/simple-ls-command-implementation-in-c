==========================================================================
		simple-ls-command-implementation-in-c
==========================================================================


This project consist of two modules, Shell command "ls" is implemented in module one. Second module copies a specified % of text from a file to another.

Write a program to
1.List the contents of Directory

2. copy data from Source file to Destination file(create file and path if not exists) of given
percentage.


Note: You should ONLY use system calls to achieve this.


Run the infinite loop until the “exit” typed.

=====================================
	USAGE DETAILS: 
=====================================

List command format:
list <directory name>

copy command format:
copy <sourceFilePath> <DestinationFilePath> <StartPercentage> <EndPercentage>

Sample Output:

copy file dir1/dir2/fileCopy1 20 60

Successfully copied :12 Bytes

list dir1

dir1 :

dir1/dir2

dir1/dir2:

dir1/dir2/fileCopy1

copy file dir1/fileCopy2 30 70

Successfully copied :11 Bytes

list dir1

dir1 :
dir1/fileCopy2
dir1/dir2
dir1/dir2:
dir1/dir2/fileCopy1
exit
