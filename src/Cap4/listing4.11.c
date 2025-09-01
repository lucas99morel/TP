#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>

struct job {
    struct job* next;
};

struct job* job_queue;
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void process_job(struct job* j) {
    /* Codigo de process_job */
}

void* thread_function(void* arg){
    while(1){
        struct job* next_job;
        pthread_mutex_lock(&job_queue_mutex);

        if (job_queue == NULL){
            next_job = NULL;
        }
        else{
            next_job = job_queue;
            job_queue = job_queue->next;
            process_job(next_job);
        }

        pthread_mutex_unlock(&job_queue_mutex);
        if (next_job == NULL){
            break;
        }

        process_job(next_job);
        free(next_job);

    }

    return NULL;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, thread_function, NULL);
    pthread_join(t, NULL);
    return 0;
}