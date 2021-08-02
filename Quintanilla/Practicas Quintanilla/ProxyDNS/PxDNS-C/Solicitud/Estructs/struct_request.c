#include "../Index_Solicitud.h"

static void encabezadoDefault ( unsigned char * paq_solicitud ) {
   unsigned char id_transaccion[2] = {0x00, 0x01};
   unsigned char indicadores[2] = {0x01, 0x00};
   unsigned char contador_repeticiones[2] = {0x00, 0x01};
   unsigned char contador_respuesta[2] = {0x00, 0x00};
   unsigned char contador_autoridades[2] = {0x00, 0x00};
   unsigned char contador_adicional[2] = {0x00, 0x00};
   memcpy( paq_solicitud + 0, id_transaccion, 2 );
   memcpy( paq_solicitud + 2, indicadores, 2 );
   memcpy( paq_solicitud + 4, contador_repeticiones, 2 );
   memcpy( paq_solicitud + 6, contador_respuesta, 2 );
   memcpy( paq_solicitud + 8, contador_autoridades, 2 );
   memcpy( paq_solicitud + 10, contador_adicional, 2 );
}

int estrucSolicitud ( unsigned char * paq_solicitud, unsigned char name_search[] ) {
    int i=0, j=0;
    encabezadoDefault( paq_solicitud );
    int tam_search = strlen(name_search);
    unsigned char name_converted[tam_search];
    for(i; i < tam_search; i++) {
        if(name_search[i] == '.' || name_search[i] == '\n') {
            name_converted[j] = (short)(i-j);
            for(j = j+1; j<i+1; j++) {
                name_converted[j] = name_search[j-1];
            }
            if(name_search[i] == '\n') name_converted[j] = 0x00;
            else j = i+1;
        }
    }
    tam_search = tam_search + 1;
    unsigned char tipo_peticion[2] = { 0x00, 0x01 };
    unsigned char clase_peticion[2] = { 0x00, 0x01 };
    memcpy( paq_solicitud + 12, name_converted, tam_search );
    memcpy( paq_solicitud + 12 + tam_search, tipo_peticion, 2 );
    memcpy( paq_solicitud + 14 + tam_search, clase_peticion, 2 );
    return ( 16 + tam_search );
}
