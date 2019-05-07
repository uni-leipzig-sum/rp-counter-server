
#include "io.h"
#include "counter.h"
#include "command.h"


static command_map_t counter_commands[] = {
  /* Analog IO */
  /* Reset all analog pins */
  { .cmd = "ANALOG:RST",         .handler = Analog_PinReset},
  /* Get the value of an analog pin in volt.
     Arg1: one of AOUT0, AOUT1, AOUT2, AOUT3, AIN0, AIN1, AIN2, AIN3 */
  { .cmd = "ANALOG:PIN?",        .handler = Analog_GetPinValue},
  /* Set the value of an analog pin in volt.
     Arg1: one of AOUT0, AOUT1, AOUT2, AOUT3, AIN0, AIN1, AIN2, AIN3
     Arg2: the value in volt */
  { .cmd = "ANALOG:PIN",         .handler = Analog_SetPinValue},

  /* Digital IO */
  /* Reset all digital pins */
  { .cmd = "DIG:RST",            .handler = Digital_PinReset},
  /* Get the state of a digital pin.
     Arg1: one of LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7,
                  DIO0_P, DIO1_P, DIO2_P, DIO3_P, DIO4_P, DIO5_P, DIO6_P, DIO7_P,
                  DIO0_N, DIO1_N, DIO2_N, DIO3_N, DIO4_N, DIO5_N, DIO6_N, DIO7_N */
  { .cmd = "DIG:PIN?",           .handler = Digital_GetPinState},
  { .cmd = "DIG:PIN",            .handler = Digital_SetPinState},
  { .cmd = "DIG:PIN:DIR?",           .handler = Digital_GetPinDirection},
  { .cmd = "DIG:PIN:DIR",            .handler = Digital_SetPinDirection},

  /* Counter */

  /* This returns the currently set counting duration (in seconds). */
  { .cmd = "COUNTER:TIME?",      .handler = Counter_GetCountingTime },
  /* This sets the counting duration. Format: "COUNTER:TIME 0.002" (time in seconds) */
  { .cmd = "COUNTER:TIME",       .handler = Counter_SetCountingTime },
  /* This command waits for any running counting processes to end and starts counting.
     Once the fresh counting process ends, it returns the counts. This is probably what
     you want most of the time!
     Response format: "700,702" (List of counts, one for each APD) */
  { .cmd = "COUNTER:COUNT?",     .handler = Counter_Count },
  /* WARNING: This might not do what you want.
     This command waits for the current counting process to end, then returns the
     counts and starts counting again. This means, you might get out of date counts.
     Response format: "700,702" (List of counts, one for each APD) */
  { .cmd = "COUNTER:WRSC?",      .handler = Counter_WaitAndReadAndStartCounting },
  COMMAND_MAP_END
};

counter_context_t counter_context = {
  .cmdlist = counter_commands
};
