#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

/* El nombre del programa */
const char* program_name;

void print_usage(FILE* stream, int exit_code){
    fprintf(stream,"Uso: %s opciones [archivo_de_entrada ...]\n",program_name);
    fprintf(stream,
            "   -h --help              Muestra esta informacion de uso.\n"
            "   -o --output filename   Escribe la salida en el archivo 'filename.'\n"
            "   -v --verbose           Muestra mensajes detallados.\n");

    exit(exit_code);
}

int main(int argc, char* argv[]){
    int next_option;

    /*Opciones cortas validas*/
    const char* const short_options = "ho:v";

    /*Opciones largas validas*/
    const struct option long_options[] = {
        {"help",        0,  NULL,   'h'},
        {"output",      0,  NULL,   'o'},
        {"verbose",     0,  NULL,   'v'},
        {NULL,          0,  NULL,   0},
    };

    /*Archivo salida del programa*/
    const char* output_filename = NULL;

    /*Bandera para verbose*/
    int verbose = 0;

    /*Nombre del programa*/
    program_name = argv[0];

    do{
        next_option = getopt_long(argc,argv,short_options,long_options,NULL);

        switch (next_option){
            case'h':
                print_usage(stdout,0);
            case 'o':
                output_filename = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case '?':
                print_usage(stderr,1);
            case -1:
                break;
            default:
                abort();
        }
    } while(next_option != -1);

    if (verbose){
        int i;
        for (i=optind; i<argc; ++i){
            printf("Argumento: %s\n",argv[i]);
        }
    }

    return 0;
}