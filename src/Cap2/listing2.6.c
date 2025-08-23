#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char* read_from_file(const char* filename, size_t lenght){
    char* buffer;
    int fd;
    ssize_t bytes_read;

    /*Reserva de memoria para los datos*/
    buffer = (char*)malloc(lenght);
    if (buffer==NULL){
        return NULL;
    }

    /*Abrir el archivo (O_RDONLY -> solo lectura!!)*/
    fd = open(filename,O_RDONLY);
    if (fd==-1){
        free(buffer);
        return NULL;
    }

    /*Se leen los datos */
    bytes_read = read(fd,buffer,lenght);
    if (bytes_read !=  lenght){
        free(buffer);
        close(fd);
        return NULL;
    }

    /*Si todo salio bien... cerrar el archivo y devolver el buffer*/
    close(fd);
    return buffer;
}