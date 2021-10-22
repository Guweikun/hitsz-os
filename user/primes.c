#include "kernel/types.h"
#include "user.h"

int p[2];
int ret;

void primes(){
    close(p[1]);
    int first;
    int tmp;
    int cnt = 0;
    int temp[35];
    int len = read(p[0], &first, sizeof(int));
    if (first == 0)
    {
        exit(0);
    }
    
    printf("prime %d\n",first);

    while (len>0)
    {
        len = read(p[0], &tmp, sizeof(int));
        if (tmp%first != 0)
        {
            temp[cnt] = tmp;
            cnt++;
        }
        
    }
    close(p[0]);

    ret = pipe(p);
    int pid = fork();
    if (pid == 0)
    {
        primes();
    }
    else if (pid > 0)
    {
        close(p[0]);
        for (int i = 0; i < cnt; i++)
        {
            write(p[1], &temp[i], sizeof(int));
        }
        close(p[1]);
    }
    wait(0);
    exit(0);
}

int main(int argc,char* argv[]){
    ret = pipe(p);

    int pid = fork();
    if (pid == 0)
    {
        primes();
    }
    else if (pid > 0)
    {
        close(p[0]);
        for (int i = 2; i < 36; i++)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
    }
    wait(0);
    exit(0);
}