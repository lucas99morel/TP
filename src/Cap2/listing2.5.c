#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int temp_file_handle;

temp_file_handle write_temp_file(char* buffer, size_t length){
    /* Archivo unico*/
    char temp_filename[] = "/tmp/temp_file.XXXXXX";
    int fd = mkstemp(temp_filename);

    /*Eliminar el archivo del sistema de archivos inmediatamente*/
    unlink(temp_filename);

    /*Escribir primero el tamaño de los datos*/
    write(fd,&length,sizeof(length));

    /*Escribir el contenido del buffer*/
    write(fd,buffer,length);

    return fd;
}

char* read_temp_file(temp_file_handle temp_file, size_t* lenght){
    char* buffer;
    int fd = temp_file;
    lseek(fd,0,SEEK_SET);
    read(fd,lenght,sizeof(*lenght));
    close(fd);
    return buffer;
}

int main(){
    return 0;
}