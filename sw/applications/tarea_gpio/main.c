#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "x-heep.h"
#include "gpio.h"
#include "timer_sdk.h"
#include "core_v_mini_mcu.h"    
#include "soc_ctrl.h"

#define GPIO_TOGGLE 0   // Pin GPIO que se va a togglear (ver constraints/pin_assign.xdc)

#if TARGET_SIM
    #define WAIT_TOGGLE 50    // 200us for simulation (so it doesn't take hours)
#else
    #define WAIT_TOGGLE 500000   // 1ms for FPGA (so it's visible on an oscilloscope)
#endif

#define PRINTF_IN_FPGA  1
#define PRINTF_IN_SIM   1

#if TARGET_SIM && PRINTF_IN_SIM
        #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#elif PRINTF_IN_FPGA && !TARGET_SIM
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#else
    #define PRINTF(...)
#endif


void __attribute__((aligned(4), interrupt)) handler_irq_timer(void) {
    timer_arm_stop();
    timer_irq_clear();
    return;   
}

int main() {


    PRINTF("--- INICIANDO TEST GPIO Y TIMER---\n");

   

    
// Configuración del pin GPIO
    uint32_t i;
    uint32_t timer_ciclos;

    timer_cycles_init();         // Inicializar el SDK del temporizador para ciclos de reloj

    gpio_result_t gpio_res;
    gpio_cfg_t pin_cfg = {
        .pin = GPIO_TOGGLE,
        .mode = GpioModeOutPushPull
    };    
    gpio_res = gpio_config (pin_cfg);
    if (gpio_res != GpioOk) {
        PRINTF("Gpio initialization failed!\n\r");
    }

    PRINTF("Starting GPIO toggle...\n\r");

    enable_timer_interrupt();

    while(1){
        // Encender
        gpio_write(GPIO_TOGGLE, true);
        PRINTF("GPIO %d ON\n\r", GPIO_TOGGLE);
        timer_wait_us(WAIT_TOGGLE); 
        timer_ciclos = timer_stop(); // Medir justo al despertar
        PRINTF("   -> Tiempo real: %u us (%u ciclos)\n\r", (uint32_t)get_time_from_cycles(timer_ciclos), timer_ciclos);

        // Apagar
        gpio_write(GPIO_TOGGLE, false);
        PRINTF("GPIO %d OFF\n\r", GPIO_TOGGLE);
        timer_wait_us(WAIT_TOGGLE);
        timer_ciclos = timer_stop();
        PRINTF("   -> Tiempo real: %u us (%u ciclos)\n\r", (uint32_t)get_time_from_cycles(timer_ciclos), timer_ciclos);
    }

    PRINTF("DEBERES DE LUIS COMPLETADOS.\n\r");

    
    return 0;
}
