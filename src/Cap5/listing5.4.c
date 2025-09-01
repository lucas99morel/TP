#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int binary_semaphore_wait(int semid){
    struct sembuf operations[1];
    operations[0].sem_num = 0;
    operations[0].sem_op = -1;
    operations[0].sem_flg = SEM_UNDO;
    return semop (semid, operations, 1);
}

int binary_semaphore_post (int semid){
    struct sembuf operations[1];
    operations[0].sem_num = 0;
    operations[0].sem_op = 1;
    operations[0].sem_flg = SEM_UNDO;
    return semop(semid, operations, 1);
}

int main(){
    int semid;

    semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Intentando entrar a la sección crítica...\n");
    binary_semaphore_wait(semid);

    printf("Dentro de la sección crítica...\n");
    sleep(3);

    printf("Saliendo de la sección crítica...\n");
    binary_semaphore_post(semid);

    semctl(semid, 0, IPC_RMID);

    return 0;
}