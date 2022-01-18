#include "hpm_common.h"
#include "hpm_soc.h"
#include <rtthread.h>

#define CONFIG_NOT_ENABLE_ICACHE (1)
#define CONFIG_NOT_ENABLE_DCACHE (1)

void system_init(void);

extern int entry(void);

extern void __libc_init_array(void);
extern void __libc_fini_array(void);

void system_init(void)
{
    disable_global_irq(CSR_MSTATUS_MIE_MASK);
    disable_irq_from_intc();
    enable_irq_from_intc();
    enable_global_irq(CSR_MSTATUS_MIE_MASK);
#ifndef CONFIG_NOT_ENABLE_ICACHE
    l1c_ic_enable(true);
#endif
#ifndef CONFIG_NOT_ENABLE_DCACHE
   // l1c_dc_enable(true);
#endif
}

__attribute__((weak)) void c_startup(void)
{
    uint32_t i;
    extern uint8_t __bss_start__, __bss_end__;
    extern uint8_t __etext, __data_start__, __data_end__;
    uint32_t size = &__bss_end__ - &__bss_start__;
    for (i = 0; i < size; i += 4) {
        *(uint32_t *)(&__bss_start__ + i) = 0;
    }

#ifdef FLASH_XIP
    extern uint8_t __vector_ram_start__, __vector_ram_end__, __vector_load_addr__;
    size = &__vector_ram_end__ - &__vector_ram_start__;
    for (i = 0; i < size; i += 4) {
        *(uint32_t *)(&__vector_ram_start__ + i) = *(uint32_t *)(&__vector_load_addr__ + i);
    }
#endif

    size = &__data_end__ - &__data_start__;
    for (i = 0; i < size; i += 4) {
        *(uint32_t *)(&__data_start__ + i) = *(uint32_t *)(&__etext + i);
    }
}

__attribute__((weak)) int main(void)
{
    while(1);
}

void reset_handler(void)
{

    /*
     * Initialize LMA/VMA sections.
     * Relocation for any sections that need to be copied from LMA to VMA.
     */
    c_startup();

    /* Call platform specific hardware initialization */
    system_init();

    /* Do global constructors */
    __libc_init_array();



    /* Entry function */
    entry();
}


__attribute__((weak)) void _init()
{
}


