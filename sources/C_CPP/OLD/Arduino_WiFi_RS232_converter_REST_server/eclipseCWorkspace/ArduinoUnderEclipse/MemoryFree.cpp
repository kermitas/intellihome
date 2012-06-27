/*
 * MemoryFree.cpp
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

#include "MemoryFree.h"

int freeRamMemory()
{
  int free_memory;

  if((int)__brkval == 0)
     free_memory = ((int)&free_memory) - ((int)&__bss_end);
  else
    free_memory = ((int)&free_memory) - ((int)__brkval);

  return free_memory;
}
