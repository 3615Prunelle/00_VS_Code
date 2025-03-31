#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFF_SIZE 40

int main (void)
{
    //const int buff_size = 10;
    char buffer[BUFF_SIZE] = {0};
    int fd = open("testfile.txt", O_RDONLY);
    int nb_read = read(fd, buffer, BUFF_SIZE); //return nb char lus
    printf ("%s", buffer);
    return (0);
}

//read buffer as many times as needed till \n >> while
//temp variable extensible >> malloc
//don't copy chars after \n >> return temp variable avec \n
//free memory