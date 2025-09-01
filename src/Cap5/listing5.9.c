#include <stdio.h>
#include <unistd.h>

int main (){
    FILE* stream = popen ("sort","w");
    fprintf (stream, "Esto es un test.\n");
    fprintf (stream, "Hola mundo.\n");
    fprintf (stream, "Mi perro tiene garrapatas\n");
    fprintf (stream, "Este programa es impresionante.\n");
    fprintf (stream, "Un pez, Dos peces...\n");
    return pclose (stream);
}