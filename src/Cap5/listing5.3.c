#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

int binary_semaphore_initialize(int semid){
    union semun argument;
    unsigned short values[1];
    values[0] = 1;
    argument.array = values;
    return semctl(semid,0,SETALL,argument);
}

int main(){
    int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if(semid == -1){
        perror("semget");
        exit(1);
    }

    if(binary_semaphore_initialize(semid) == -1){
        perror("semctl - initialize");
        exit(1);
    }

    printf("Semáforo inicializado en 1\n");

    semctl(semid, 0, IPC_RMID); 
    return 0;
}