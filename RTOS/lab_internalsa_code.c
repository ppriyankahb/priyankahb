#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    int id1,id2,id3;
    int status;
    int count=0,count1=0,count2=0;
    int ch;
    id1=fork();
    if(id1<0)
    {
        printf("error");
        exit(0);
    }

    else if(id1==0)
    {
        execl("/bin/ls","ls","-l",NULL);
        perror("exec");
    }else{
        waitpid(id1,&status,0);

    id2=fork();
    if(id2<0)
    {
        printf("error");
        exit(0);
    }

    else if(id2==0)
    {
        execl("/bin/pwd","pwd",NULL);
        perror("exec");
    }else{
        waitpid(id2,&status,0);
    
    id3=fork();
    if(id3<0)
    {
        printf("error");
        exit(0);
    }

    else if(id3==0)
    {
        FILE *f1;

        f1=fopen("example2.txt","w");

        if(f1==NULL)
        {
            printf("error msg");
            exit(0);
        }
        fprintf(f1,"aaaxxxzzzz14278759627600shfiwaghpeK'e;bnolaebp;aeb57974631374611\n");
        
        while((ch=getc(f1))!=EOF)
        putc(ch,f1);
        fclose(f1);

        f1=fopen("example2.txt","r");

        if(f1==NULL)
        {
            printf("error msg");
            exit(0);
        }

        while((ch=getc(f1))!=EOF)
        {
    
            if(ch=='a')
            count++;
            else if(ch=='z')
            count1++;
            else if(ch>='0' && ch<='9')
            count2++;
        }
        printf("sum of 'a' is %d\n,sum of 'z' is %d\n,sum of digits are %d\n",count,count1,count2);

        fclose(f1);
        
    }else{
        waitpid(id3,&status,0);

    }
    }
    }
    return 0;
}