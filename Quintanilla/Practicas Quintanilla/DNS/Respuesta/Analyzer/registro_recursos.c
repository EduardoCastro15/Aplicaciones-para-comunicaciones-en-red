#include "../Index_Respuesta.h"

int tipo;

static int leerNom ( unsigned char paq_respuesta[], int position) {
   int apuntador, i;
   do {
      if( paq_respuesta[position] == 0xC0 ) {
         apuntador = paq_respuesta[position + 1];
         do {
            for( i=1; i <= paq_respuesta [apuntador]; i++ ) {
               printf("%c", paq_respuesta [apuntador + i]);
            }
            apuntador = apuntador + i;
            if( paq_respuesta [apuntador] == 0xC0 ) {
               printf(".");
               leerNom( paq_respuesta, apuntador );
               return position + 2;
               break;
            }
            if( paq_respuesta [apuntador] == 0x00) {
               return position + 2;
               break;
            } else {
               printf(".");
            }
         } while (1);
         break;
      } else {
         do {
            if( paq_respuesta [position] == 0xC0 ) { break; }
            for( i=1; i <= paq_respuesta [position]; i++ ) {
               printf("%c", paq_respuesta [position + i]);
            }
            position = position + i;
            if( paq_respuesta [position] == 0x00) {
               printf(":  ");
               position = position + i;
               break;
            } else {
               printf(".");
            }
         } while (1);
      }
   } while (1);
}

static int leerIP ( unsigned char paq_respuesta[], int position) {
   printf("%i.%i.",paq_respuesta[position], paq_respuesta[position+1]);
   printf("%i.%i",paq_respuesta[position+2], paq_respuesta[position+3]);
   return position+4;
}

static int tipeClass( unsigned char paq_respuesta[], int position ) {
   tipo = paq_respuesta [position+1];
   if( paq_respuesta [position+1] == 0x01) { printf("tipo: RegistroHost  "); }
   else if( paq_respuesta [position+1] == 0x02) { printf("tipo: A  "); }
   else if( paq_respuesta [position+1] == 0x05) { printf("tipo: CNAME  "); }
   printf("clase: IN  ");
   return position + 4;
}

static int readAll( unsigned char paq_respuesta[], int position ) {
   int tam;
   printf("    --> ");
   position = leerNom( paq_respuesta, position);
   printf(":  ");
   position = tipeClass( paq_respuesta, position );
   printf("TTL: %i,  ", (paq_respuesta[position]<<24) | (paq_respuesta[position+1]<<16) |
      (paq_respuesta[position + 2]<<8) | paq_respuesta[position + 3] );
   tam = htons(((paq_respuesta[position + 4] << 8) &0xFF00) | (paq_respuesta[position + 5] & 0xFF));
   position = position + 6;
   if( tipo == 0x01 ) {
      printf("addr ");
      position = leerIP( paq_respuesta, position );
      printf("\n");
   }
   else if( tipo == 0x02 ) {
      printf("ns ");
      position = leerNom( paq_respuesta, position );
      printf("\n");
   }
   else if( tipo == 0x05 ) {
      printf("cname ");
      position = leerNom( paq_respuesta, position );
      printf("\n");
   }
   return position;
}

void readRR ( unsigned char paq_respuesta[], int position ) {
   int i;
   int answer = htons(((paq_respuesta[7] << 8) &0xFF00) | (paq_respuesta[6] & 0xFF));
   int authority = htons(((paq_respuesta[9] << 8) &0xFF00) | (paq_respuesta[8] & 0xFF));
   int additional = htons(((paq_respuesta[11] << 8) &0xFF00) | (paq_respuesta[10] & 0xFF));
   if( answer ) { //Answer
      printf("  --> Answer:\n");
      for(i=0; i < answer; i++) { position = readAll( paq_respuesta, position ); }
   }
   if( authority ) { //Authority
      printf("  --> Authority:\n");
      for(i=0; i < authority; i++) { position = readAll( paq_respuesta, position ); }
   }
   if( additional ) { //Additional
      printf("  --> Additional:\n");
      for(i=0; i < authority; i++) { position = readAll( paq_respuesta, position ); }
   }
}
