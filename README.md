Exercise 6. (55 points) Complete the fileutil program, as described below. Do not use libc, but rather, expand the use of your own system call macros, implemented in mysyscall.h. 
The program should build on the course VMs, using the 'make' command. The program should take arguments as follows:

	 fileutil [-cdhru] infile|- outfile|-
	 
The program will read infile and write outfile, or write to standard output if given '-'. The program will also take the following options (any, all, or none):

-c: Count the newlines in the file and output this on stderr (file handle 2)
-d: Convert the output to use DOS-style newlines (carriage-return, line feed). Display an error message and help if used with -u.
-h: Print a help message and exit.
-r: Reverse the contents of the file, on a line-by-line basis. For instance: "I love CSE 306.\nCSE 306 is fun!\n" should appear as "CSE 306 is fun!\nI love CSE306.\n".
-u: Convert the output to use Unix-style newlines (line feed only). Display an error message and help if used with -d.
The file names given as input can be any kind of files: relative pathnames or absolute ones. The input file must exist before the program can succeed. The output file may or may not exist: if it exists, it's OK to overwrite it but only if you won't damage the input file (i.e., the infile and outfile may be the same). 
You should support both syntax like

    fileutil -cdr in.txt out.txt
    
as well as

    fileutil -c -d -r in.txt out.txt
    
although this is a lower-priority feature. 
As special names, if infile is "-", you should read from stdin. If outfile is "-", you should output to stdout. That way, you can use the fileutil program as a "Unix filter" such as

$ cat foo.in | ./fileutil -d - foo.out
or
$ ./fileutil foo.in - > foo.out
The program should check for EVERY POSSIBLE ERROR that could occur BEFORE opening the input and output files and while changing the file data. In the case of a possible error, the program should print a detailed error message on stderr and exit with a non-zero status code. This means that you should, for example, check that the input files are readable, that you have permission to read and/or write them (as needed), that neither is a directory, character/block special device, etc. Other errors could occur, and it is your job to write the code that checks for all of those conditions. (A good way to think about it is to inspect manual pages for the system calls that you use, and think to yourself "what else could go wrong when this function runs"). Some of the more complex error conditions for which you should check is running out of disk space or quota, or when the two file arguments use different names but actually point to the same file (do not try to modify a file in place -- this may corrupt the file). 

Many of the possible errors are listed on the analogous libc manual page. For instance, you might look at man 2 open to learn all possible return values (however, the error will be a directly returned as a negative value, not placed in errno). 

You are welcome to include the definitions in standard header files, but you may not link against libc, or include .c files from the libc source. 
