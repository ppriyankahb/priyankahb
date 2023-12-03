/*1. To demonstrate the usage of the various shared memory system 
calls- WAP which creates a shared memory segment of length 100 bytes
and writes 'A' to 'Z' to it. 
Next, let the same program access the segment area and display its 
contents to the screen (all 100 bytes).Let the program next convert 
the case of the alphabets in the segment to lowercase. Finally let 
the program access the same area and display the segment contents 
once again to the screen. Observe the output.*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<ctype.h>
#include<unistd.h>

int main()
{
    int seg_id;
    const int len=100;
    char *sm;

    seg_id=shmget(IPC_PRIVATE,len,S_IRUSR|S_IWUSR);
    sm=(char*)shmat(seg_id,NULL,0);
    for(int i=0;i<26;i++)
    sm[i]='A'+i;

    printf("the contents is\n");
    for(int i=0;i<26;i++)
    printf("%c\n",sm[i]);

    for(int i=0;i<26;i++)
    sm[i]=tolower(sm[i]);

    printf("converted characters are");
    for(int i=0;i<26;i++)
    printf("%c\n",sm[i]);

    shmdt(sm);
    shmctl(seg_id,IPC_RMID,NULL);
    return 0;
}