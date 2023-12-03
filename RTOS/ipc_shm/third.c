/*3. Let a parent process create a segment of length 2k and write n 
strings to the area. Let the value of n be passed as a commandline 
argument. Next, let the parent fork a child.Let the child capitalise 
the first character of each string.Once the child completes let the 
parent access the shared area and display their contents to the 
screen.
*/

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
    char *sm;
    int len=2000;
    seg_id=shmget(IPC_PRIVATE,len,S_IRUSR|S_IWUSR);
    sm=(char*)shmat(seg_id,NULL,0);
    int id;
    char *str;
    int n;
     printf("enter the value of n\n");
        scanf("%d",&n);
printf("enter the strings\n");
        for(int i=0;i<=n;i++){
        //sm[i]=malloc(sizeof(char)*2000);
        
        fgets(sm + (i * 100), 100, stdin);
        }
        
    id=fork();
    if(id<0)
    {
        printf("error");
        exit(0);
    }
    else if(id==0)
    {for(int i=0;i<=n;i++)
       sm[i * 100] = toupper(sm[i * 100]);
    }else{
        wait(NULL);
        for(int i=0;i<=n;i++)
        printf("%s", sm + (i * 100));
        
    }
    shmdt(sm);
        shmctl(seg_id,IPC_RMID,NULL);
    return 0;
}