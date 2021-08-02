#include "../Index_Respuesta.h"

static int readQueri ( unsigned char paq_respuesta[] ) {
   int i, position=12;
   printf("\n--> Queri\n");
   printf("  --> ");
   do {
      for( i=1; i <= paq_respuesta [position]; i++) {
         printf("%c", paq_respuesta [position+i]);
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
   if( paq_respuesta [position+1] == 0x01) { printf("tipo: RegistroHost  "); }
   else if( paq_respuesta [position+1] == 0x02) { printf("tipo: A  "); }
   else if( paq_respuesta [position+1] == 0x05) { printf("tipo: CNAME  "); }
   printf("clase: IN(0X0001)\n");
   return position + 2;
}

int readHeader ( unsigned char paq_respuesta[] ) {
   printf( "  --> ID: %i\n", htons( ( ( paq_respuesta[1] << 8 ) &0xFF00 ) |
      ( paq_respuesta[0] & 0xFF ) ) );
   printf( "  --> Flags: %.2X %.2X\n", paq_respuesta[2], paq_respuesta[3] );
   if(1) { if( (paq_respuesta[2] & 0x04) == 0x04 ) {
      printf("     --> Autoridad: Si\n"); } else{ printf("     --> Autoridad: No\n"); }}
   if(1) { if( (paq_respuesta[2] & 0x02) == 0x02 ) {
      printf("     --> Trunco: Si\n"); } else{ printf("     --> Trunco: No\n"); }}
   if(1) { if( (paq_respuesta[2] & 0x01) == 0x01 ) {
      printf("     --> Recursion: Activa\n"); } else{ printf("     --> Recursion: Desactivada\n"); }}
   if(1) { if( (paq_respuesta[3] & 0x80) == 0x80 ) {
      printf("     --> Recursion Disponible: Si\n"); } else{ printf("     --> Recursion Disponible: No\n"); }}
   if(1) { if( (paq_respuesta[3] & 0x05 ) == 0x05 || (paq_respuesta[3] & 0x03) == 0x03) {
      printf("     --> Codigo de Retorno: Error\n"); exit(0); } else{
         printf("     --> Codigo de Retorno: Success\n"); }}
   printf("  --> Questions: %i\n", htons(((paq_respuesta[5] << 8) &0xFF00) | (paq_respuesta[4] & 0xFF)));
   printf("  --> Answer RRs: %i\n", htons(((paq_respuesta[7] << 8) &0xFF00) | (paq_respuesta[6] & 0xFF)));
   printf("  --> Authority RRs: %i\n", htons(((paq_respuesta[9] << 8) &0xFF00) | (paq_respuesta[8] & 0xFF)));
   printf("  --> Additional RRs: %i\n", htons(((paq_respuesta[11] << 8) &0xFF00) | (paq_respuesta[10] & 0xFF)));
   return readQueri( paq_respuesta );
}
