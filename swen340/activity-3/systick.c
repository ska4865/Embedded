#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <systick.h>

int main(int arg_count, char *arg_list[]){
    // Make a pointer to systick_t
    // Assign it to the first address in the sys tick registers
    // Change a value
    
    systick_t* p_timer;
    p_timer = (systick_t*) 0xE0000000;

    printf("CSR - %d\n", p_timer->SYST_CSR);

}