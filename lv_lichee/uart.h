#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

int fd1,fd2,nByte;
char *uart1;
char *uart2;
char bufferk[16];
char buffera[16];

int set_opt(int,int,int,char,int);
