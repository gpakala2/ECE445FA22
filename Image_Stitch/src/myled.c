#include "myled.h"


void map_gpios(void)
{
 int fd;
 if ((fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0)
 if (fd < 0) {
 perror("/dev/mem");
 exit(-1);
 }
 leds = (volatile uint32_t*)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED,fd, leds_addr);
 if (leds == MAP_FAILED) {
 perror("leds did not get pointer from mmap");
 exit(-1);
 }
 buttons = (volatile uint32_t*)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED,fd, buttons_addr);
 if (buttons == MAP_FAILED) {
  perror("buttons did not get pointer from mmap");
  exit(-1);
 }
 pmod = (volatile uint32_t*)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED,fd, pmod_addr);
  if (pmod == MAP_FAILED) {
   perror("pmod did not get pointer from mmap");
   exit(-1);
  }
}

int select_mode(void)
{
 int mode;
 printf("Select one of the following modes:\r\n");

 printf("%0d) Enter a value to write to the GPIO LEDs.\r\n",leds_mode);
 printf("%0d) Exit the demo.\r\n",exit_mode);
 scanf("%d",&mode);
 return mode;
}
void run_leds_mode(int val)
{
 //printf("Enter a value to set the IO LEDs to: led = %x\r\n",(unsigned int)leds);

 *leds = val;
}
void run_pmod_mode(void)
{
 int val;
 printf("Enter a value to set the IO PMOD to: PMOD = %x\r\n",(unsigned int)pmod);
 //setting all pins to output
 *(pmod+4) = 0x00;
 scanf("%d",&val);
 *pmod = val;
}
uint32_t run_buttons_mode(void)
{
 //int val;
// printf("Read value from buttons: Buttons = %x\r\n",(unsigned int)buttons);
 //printf("Button value is: %0d\n", *buttons);
 return *buttons;
}
int start_leds(int config)
{
 int mode;
//printf("Hello, PetaLinux World LED!\n");

//printf("gpi_custom inside main:\r\n");
 map_gpios();
 //if config, launch program
 if (config) {
 do {
 mode = select_mode();
 if (mode == leds_mode)
 run_leds_mode(15);
 if (mode == pmod_mode)
  run_pmod_mode();
 if (mode == buttons_mode)
   run_buttons_mode();
 } while (mode != exit_mode);
 }
 return 0;
}
