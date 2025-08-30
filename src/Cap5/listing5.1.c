#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(){
    int segment_id;
    char* shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400;

    segment_id = shmget(IPC_PRIVATE,shared_segment_size,
                        IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    shared_memory = (char*)shmat(segment_id,0,0);
    printf("Memoria compartida asignada en la direccion: %p\n",shared_memory);

    shmctl(segment_id,IPC_STAT,&shmbuffer);
    segment_size = shmbuffer.shm_segsz;

    printf("Tamaño del segmento: %d\n",segment_size);
    sprintf(shared_memory,"Hola Mundo");
    shmdt(shared_memory);

    shmctl(segment_id,IPC_RMID,0);

    return 0;
}