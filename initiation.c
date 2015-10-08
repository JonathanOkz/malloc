/*
** initiation.c
** 
** Made by oleszkiewicz Jonathan
** Email   <JonathanOlesz@gmail.com>
** 
** Started on  Sun Feb 16 22:03:30 2014 oleszkiewicz
** Last update Sun Feb 16 22:03:32 2014 oleszkiewicz
*/

#include "malloc.h"

/**
* Initialise la structure t_list lors du premier appel à malloc
* @param void
* @return void
*/
void    initiation()
{
  static bool  initiation=false;

  if (initiation == true) return;

  list.beg = NULL;
  list.last = NULL;
  list.sizePage = getpagesize();
  list.pnt_end_list = sbrk(0);
  list.pnt_end_mem = list.pnt_end_list;

  initiation = true;
}


