#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
        char buf, arg[1024], *args[MAXARG];
        int pid, n, buf_index = 0;
        
        for (int i = 1; i < argc; i++){
                args[i-1] = argv[i];
        }
        
        args[argc-1] = arg;
        args[argc] = 0;
        
        while ((n = read(0, &buf, 1)) > 0){
                if (buf == '\n' || buf == ' '){
                        arg[buf_index] = 0;
                        if ((pid = fork()) < 0){
                                fprintf(2, "An error occured.\n");
                                exit(1);
                        }
                        else if (pid == 0){
                                exec(args[0], args);
                        }
                        else{
                                wait(0);
                                buf_index = 0;
                        }

                }
                else{
                        arg[buf_index++] = buf;
                }
        }
        if (n < 0){
                fprintf(2, "An error occurred.\n");
                exit(1);
        }
        exit(0);
}
