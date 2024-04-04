/*
 * software_timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: HTH
 */

#include "software_timer.h"

int timer0_counter = 0;
int timer0_flag = 0;

int timer1_counter = 0;
int timer1_flag = 0;

void setTimer0(int time)
{
  timer0_counter = time;
  timer0_flag = 0;
}
void setTimer1(int time)
{
  timer1_counter = time;
  timer1_flag = 0;
}

void timerRun()
{
  if (timer1_counter > 0)
  {
    timer1_counter--;
    if (timer1_counter <= 0)
    {
      timer1_flag = 1;
    }
  }
  if (timer0_counter > 0)
  {
    timer0_counter--;
    if (timer0_counter <= 0)
    {
      timer0_flag = 1;
    }
  }
}