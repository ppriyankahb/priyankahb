#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>

int main()
{
    int seg_id;
    int len=4096;

    char *sm;

    seg_id=shmget(IPC_PRIVATE,len,S_IRUSR|S_IWUSR);
    sm=(char*)shmat(seg_id,NULL,0);
    sprintf(sm,"hello");
    printf("%s",sm);
    shmdt(sm);
    shmctl(seg_id,IPC_RMID,NULL);
    return 0;
}