/* 3.27
 * Design a file-copying program named filecopy.c using ordinary
 * pipes. This program will be passed two parameters: the name of the file
 * to be copied and the name of the destination file. The program will then
 * create an ordinary pipe and write the contents of the file to be copied to
 * the pipe. The child process will read this file from the pipe and write it
 * to the destination file. For example, if we invoke the program as follows:
 * 
 * 		./filecopy input.txt copy.txt
 * 
 * the file input.txt will be written to the pipe. The child process will read
 * the contents of this file and write it to the destination file copy.txt. You 
 * may write this program using either UNIX or Windows pipes.
 */