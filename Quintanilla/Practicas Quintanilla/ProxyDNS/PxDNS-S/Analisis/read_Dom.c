#include "../Index.h"

int readDom ( unsigned char paq_cliente[] ) {
   int i, position=12;
   do {
      for( i=1; i <= paq_cliente [position]; i++ ) {}
      position = position + i;
      if( paq_cliente [position] == 0x00){ break; }
   } while (1);
   if( paq_cliente [position-1] == 'x' && paq_cliente [position-2] == 'm' &&
      paq_cliente [position-4] == 'n' && paq_cliente [position-5] == 'p' &&
      paq_cliente [position-6] == 'i' ) {
         printf("  --> Solicitud Correcta\n"); return 1;
      } else { printf("  --x Solicitud Incorrecta\n\n"); return 0; }
}
