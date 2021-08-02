#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    unsigned char dato;
    unsigned char dat[512];
    int i=0,n;
    FILE *fr, *fw;

    fr = fopen("Dinero.jpg", "rb");
    // fr = fopen("datos.txt", "rb");
    fw = fopen("salida", "wb");
    if(fr==NULL){perror("Error al abrir archivo"); exit(1);}
    if(fw==NULL){perror("Error al abrir archivo"); exit(1);}
    while (!feof(fr)) {
               n = fread(dat, 1, 512, fr);
               i+=n;
               printf("n = %d\n", n);
               fwrite(dat, 1, n, fw);
           }
           printf("%d bytes read from library",i);
    fclose(fw);
    fclose(fr);

    return 0;
}