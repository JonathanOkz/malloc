/*
** fusion.c
** 
** Made by oleszkiewicz Jonathan
** Email   <JonathanOlesz@gmail.com>
** 
** Started on  Sun Feb 16 22:02:09 2014 oleszkiewicz
** Last update Sun Feb 16 22:19:33 2014 oleszkiewicz
*/

#include "malloc.h"

/*
* fonction testant s'il est possible de fusionner le block mémoire désigné par "p" (qui est free) avec le block précédent. A noter que pour que la fusion puisse s'opérer il faut que le block précédent soient free
* @param p: pointeur sur un pointeur de type t_block
* @return void
*/
void    fusion_with_prev_block(t_block **p)
{
  if ((*p)->prev && (*p)->prev->free == true)
    {
      if ((*p)->next)
        (*p)->prev->size = (void *)(*p)->next - (void *)(*p)->prev->pnt;
      else
        (*p)->prev->size = (void *)list.pnt_end_list - (void *)(*p)->prev->pnt;

      (*p)->prev->next = (*p)->next;
      
      if ((*p) == list.last)
        list.last = (*p)->prev;
      else
        (*p)->next->prev = (*p)->prev;
      
      (*p) = (*p)->prev;
    }
}

/*
* fonction testant s'il est possible de fusionner le block mémoire désigné par "p" (qui est free) avec le block suivant. A noter que pour que la fusion puisse s'opérer il faut que le block suivant soient free
* @param p: pointeur sur un pointeur de type t_block
* @return void
*/
void    fusion_with_next_block(t_block **p)
{
  if ((*p)->next && (*p)->next->free == true)
    {
      if ((*p)->next == list.last)
        list.last = (*p);
      else
        (*p)->next->next->prev = (*p);

      if ((*p)->next->next)
        (*p)->size = (void *)(*p)->next->next - (void *)(*p)->pnt;
      else
        (*p)->size = (void *)list.pnt_end_list - (void *)(*p)->pnt;
      
      (*p)->next = (*p)->next->next;
    }
}

/*
* fonction testant s'il est possible de fusionner le block mémoire désigné par "p" (qui est free) avec le block suivant ou le block précédent. A noter que pour que la fusion puisse s'opérer il faut que l'un ou les deux blocks juxtaposés soient free
* @param p: pointeur sur un pointeur de type t_block
* @return void
*/
void	 fusion(t_block **p)
{
  fusion_with_prev_block(p);
  fusion_with_next_block(p);
}
