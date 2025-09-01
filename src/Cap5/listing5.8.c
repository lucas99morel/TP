#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (){
    int fds[2];
    pid_t pid;

    pipe(fds);
    pid = fork();
    if (pid == (pid_t) 0) {
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        execlp("sort", "sort", NULL);
    }
    else{
        FILE* stream;
        close(fds[0]);
        stream = fdopen(fds[1], "w");
        fprintf(stream, "Esto es un test.\n");
        fprintf(stream, "Hola mundo.\n");
        fprintf(stream, "Mi perro tiene pulgas\n");
        fprintf(stream, "Este programa es horrible.\n");
        fprintf(stream, "Un pez, Dos peces...\n");
        fflush(stream);
        close(fds[1]);
        waitpid(pid, NULL, 0);
    }
    return 0;
}