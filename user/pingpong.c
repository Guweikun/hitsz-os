#include "kernel/types.h"
#include "user.h"

int main(int argc,char* argv[]){
    int p[2];
    int o[2];
    int ret,ret1;
    char buffer[4];
    char buffer1[4];

    ret = pipe(p);
    ret1 = pipe(o);

    if (ret < 0 || ret1 < 0)
    {
        /* code */
        printf("pipe error");
    }

    int pid = fork();
    if (pid == 0)
    {
        /* 子进程 */
        close(p[1]);
        int r_len = read(p[0],buffer,4);
        if (r_len < 0)
        {
            /* code */
            printf("read error");
        }
        close(p[0]);
        printf("%d: received %s\n",getpid(),buffer);

        close(o[0]);
        int w_len = write(o[1],"pong",4);
        if (w_len < 0)
        {
            /* code */
            printf("write error");
        }
        close(o[1]);
        
        
    }
    else if (pid > 0)
    {
        /* code */
        close(p[0]);
        int w_len = write(p[1],"ping",4);
        if (w_len < 0)
        {
            /* code */
            printf("write error");
        }
        close(p[1]);

        
        close(o[1]);
        int r_len = read(o[0],buffer1,4);
        if (r_len < 0)
        {
            /* code */
            printf("read error");
        }
        close(o[0]);
        printf("%d: received %s\n",getpid(),buffer1);
    }
    
    exit(0); //确保进程退出
}
