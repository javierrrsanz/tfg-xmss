#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("--- INICIANDO TEST XMSS ---\n");
    
    int a = 5;
    int b = 10;
    int resultado = a + b;
    
    printf("Calculando en RISC-V: %d + %d = %d\n", a, b, resultado);
    
    if (resultado == 15) {
        printf("¡EL PROCESADOR FUNCIONA PERFECTO!\n");
    }

    printf("--- FIN DEL TEST ---\n");
    return 0;
}
