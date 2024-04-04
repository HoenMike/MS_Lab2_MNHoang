/*
 * software_timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: HTH
 */

#include "software_timer.h"

int timer1_counter = 0;
int timer1_flag = 0;

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
}