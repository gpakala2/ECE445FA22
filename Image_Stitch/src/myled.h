#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/mman.h>


static volatile uint32_t *leds;
static const uint32_t leds_addr = 0x81210000;

static volatile uint32_t *buttons;
static const uint32_t buttons_addr = 0x81200000;

static volatile uint32_t *pmod;
static const uint32_t pmod_addr = 0x80000000;

const int leds_mode = 5;
const int buttons_mode = 6;
const int pmod_mode = 7;


const int exit_mode = 0;


void map_gpios(void);
int select_mode(void);
void run_leds_mode(int val);
uint32_t run_buttons_mode(void);
void run_pmod_mode(void);

int start_leds(int config);



