#include <stdio.h>
#include "listing1.3.hpp" //reciprocal.hpp

int main(int argc, char **argv){
    int i;

    i = atoi(argv[1]);
    printf("El reciproco de %d es %g\n",i,reciprocal(i));
    return 0;
}