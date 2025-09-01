#include <sys/ipc.h>
#include <sys/sem.h>
#include<stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

int binary_semaphore_allocation(key_t key,int sem_flags){
    return semget(key,1,sem_flags);
}

int binary_semaphore_desallocate(int semid){
    union semun ignored_argument;
    return semctl(semid,1,IPC_RMID,ignored_argument);
}

int binary_semaphore_initialize(int semid){
    union semun argument;
    unsigned short values[1];
    values[0] = 1;
    argument.array = values;
    return semctl(semid,0,SETALL,argument);
}

int main(){
    int semid = binary_semaphore_allocation(IPC_PRIVATE,0666|IPC_CREAT);
    binary_semaphore_initialize(semid);

    struct sembuf sb = {0,-1,0};
    semop(semid,&sb,1);
    printf("Seccion critica...\n");
    sleep(2);
    sb.sem_op = 1;
    semop(semid,&sb,1);

    binary_semaphore_desallocate(semid);
    return 0;
}