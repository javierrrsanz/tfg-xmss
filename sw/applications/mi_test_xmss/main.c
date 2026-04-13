#include <stdint.h>
#include <stddef.h>
#include "xmss.h"

// 1. Clave Pública (68 bytes para XMSS-SHA2_10_256)
const unsigned char pk[68] = { 
    /* PEGA AQUÍ TUS DATOS HEX SEPARADOS POR COMAS (ej: 0x00, 0x01...) */ 
};

// 2. Firma WOTS+ + Auth Path + Mensaje Original
// El tamaño es params.sig_bytes + longitud de tu mensaje. Para h=10 es aprox 2532.
const unsigned char sm[2532] = { 
    /* PEGA AQUÍ TUS DATOS HEX SEPARADOS POR COMAS */ 
};
const unsigned long long smlen = sizeof(sm);

// 3. Buffer de salida para recuperar el mensaje si la firma es válida
unsigned char m_out[32]; // Ajusta el tamaño si tu mensaje original ocupa más bytes
unsigned long long mlen_out;

int main() {
    // Usamos volatile para evitar que el compilador optimice y borre la variable
    volatile int status = -1; 

    // xmss_sign_open devuelve 0 si la validación es matemáticamente correcta
    status = xmss_sign_open(m_out, &mlen_out, sm, smlen, pk);

    if (status == 0) {
        // VERIFICACIÓN EXITOSA. Bucle infinito para poder atraparlo en simulación.
        while(1) {
            __asm__ volatile ("nop"); 
        }
    } else {
        // VERIFICACIÓN FALLIDA.
        while(1) {
            __asm__ volatile ("nop");
        }
    }

    return status;
}