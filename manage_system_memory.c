/*
** manage_system_memory.c
** 
** Made by oleszkiewicz Jonathan
** Email   <JonathanOlesz@gmail.com>
** 
** Started on  Sun Feb 16 22:02:09 2014 oleszkiewicz
** Last update Sun Feb 16 22:19:33 2014 oleszkiewicz
*/

#include "malloc.h"

/**
* Si la zone mémoire contenue entre list.pnt_end_list et list.pnt_end_mem est supérieure ou égale à x pagesize on rend la mémoire au system en utilisant la fonction sbrk()
* @param void
* @return void
*/
void 		deallocate_pageSize_memory()
{
  size_t	size;
  size_t	tmp_size;

  if ((size_t)(list.pnt_end_mem - list.pnt_end_list) >= list.sizePage)
    {
      tmp_size = list.pnt_end_mem - list.pnt_end_list;
      size = (tmp_size / list.sizePage) * list.sizePage;
      list.pnt_end_mem -= size;
      if (sbrk((int)size * -1) == (void *)-1) exit(0);
    }
}

/**
* Si la zone mémoire contenue entre list.pnt_end_list et list.pnt_end_mem est inferieur à sizeof(t_block) + size on alloue x pagesize  en utilisant la fonction sbrk() 
* @param size: taille de l'allocation mémoire demandée
* @return void
*/
void    allocate_pageSize_memory(size_t size)
{
  size_t  memory_wanting;
  size_t  memory_takes;

  if (sizeof(t_block) + size > (size_t)(list.pnt_end_mem - list.pnt_end_list))
    {
      memory_wanting = (sizeof(t_block) + size - (list.pnt_end_mem - list.pnt_end_list));
      memory_takes = (memory_wanting / list.sizePage + 1) * list.sizePage;
      if (sbrk(memory_takes) == (void *)-1) exit(0);
      list.pnt_end_mem += (memory_takes);
    }
}
