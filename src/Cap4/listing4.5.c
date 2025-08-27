#include <pthread.h>

void* thread_function (void* thread_arg){
    /* Codigo del thread... */
}

int main (){
    pthread_attr_t attr;
    pthread_t thread;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread, &attr, &thread_function, NULL);
    pthread_attr_destroy(&attr);
    /* Codigo restante... */
    /* No hace falta join, porque el hilo ahora es DETACHED. */
    return 0;
}