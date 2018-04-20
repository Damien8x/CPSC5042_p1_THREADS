Damien Sudol
p1 README
04/16/18

********************************************************************
			VowelFinder.cpp Read Me

Thank-you for choosing VowelFinder, the program using concurrent 
programming to track all your vowels!
VowelFinder is designed to accept a directory path from the user.
File path should lead to a directory of 20 files, with the naming
convention file1.txt, file2.txt ..... file19.txt, file20.txt .
VowelFinder will keep a running total of each respective vowel 
accross all files. After all files have been processed VowelFinder 
will print a vowel, followed by the total found accross all files.
Upper and lowercase vowels will be treated as equivalent.

********************************************************************
			Entering File Path

There are three acceptable ways to enter the filepath. 
VowelFinder will prompt user to enter the file path leading 
to the directory holding files to be processed.
1)

One file path possibility would be to enter an equivalent to a "pwd"
as if you were in said directory which contains files. 
Path should NOT end with a "/".

Example:
	/home/[user]/Documents/FileFolder


2)
User may also enter file path from the directory they are currently
in. For example, if you are Files are in:

	 /home/[user]/Documents/FileFolder

and you are currently in /home/[user] . program would accept
the file path:

	Documents/FileFolder

3)
If user is currently within the directory where target files are 
contained they may simply hit the "return" key, with no text or 
white space. 


**If file path is incorrect or necessasry files are not present within
the direcotry, program will provide an error message and exit the 
program.

*********************************************************************
			Compiling VowelFinder.cpp

VowelFinder uses elements of c++11 and pthreads. To compile and run
VowelFinder please follow the below instructions.

	1)Ensure CWD contains file VowelFinder.cpp
	2)Enter the command:
			g++ -std=c++11 VowelFinder.cpp -lpthread
	3)Next, to run VowelFinder enter command:
			./a.out
	4)Follow above instructions for "Entering File Path"
				

