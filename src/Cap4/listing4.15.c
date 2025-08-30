#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* thread_function(void* arg){
    fprintf(stderr,"El PID de hilo hijo es %d\n",(int)getpid());
    /* Ciclo infinito */
    while (1);
    return NULL;
}
int main (){
    pthread_t thread;
    fprintf (stderr,"El PID del hilo main es %d\n", (int)getpid());
    pthread_create(&thread, NULL, &thread_function, NULL);
    /* Ciclo infinito */
    while (1);
    return 0;
}