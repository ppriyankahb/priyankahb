/*2. Let a parent process create a segment of adequate length and 
write 0 to 9 as well as 'a' to 'z' to it.Next, let the parent fork a 
child.Let the child increment all the integers by a value 100. Also 
let it convert all the characters to upper case. Once the child 
completes, let the parent access the shared area and display their 
contents to the screen.*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<ctype.h>
#include<unistd.h>
#include<wait.h>

int main()
{
    int seg_id;
    const int len=100;
    char *sm;

    seg_id=shmget(IPC_PRIVATE,len,S_IRUSR|S_IWUSR);
    sm=(char*)shmat(seg_id,NULL,0);

    for(int i=0;i<10;i++)
    sm[i]='0'+i;

    for(int i=10;i<36;i++)
    sm[i]='a'+i-10;

    int id;
    id=fork();
    if(id<0)
    {
        printf("error");
        exit(0);
    }
    else if(id==0){
        //printf("uppercase letters\n");
        for(int i=0;i<10;i++)
        sm[i]=sm[i]+100;

        for(int i=10;i<36;i++)
        sm[i]=toupper(sm[i]);

    shmdt(sm);
    exit(0);
    }
    else{
        wait(NULL);
        for(int i=0;i<100;i++)
        printf("%c",sm[i]);
    shmdt(sm);
    shmctl(seg_id,IPC_RMID,NULL);
    }
    
    return 0;
}