/*
** main_function.c
** 
** Made by oleszkiewicz Jonathan
** Email   <JonathanOlesz@gmail.com>
** 
** Started on  Sun Feb 16 22:04:11 2014 oleszkiewicz
** Last update Sun Feb 16 22:13:09 2014 oleszkiewicz
*/

#include "malloc.h"

/**
* alloue size octets de mémoire au système 
* @param size: taille de l'allocation memoire demandée
* @return pointeur sur la zone mémoire allouée
*/
void		  *malloc(size_t size)
{
  t_block *pnt;

  initiation();
  pthread_mutex_lock(&list.mutex);
  pnt = search_free_block(size);
  if (pnt != NULL)
    {
      set_attribute_block(pnt, size);
    }
  else
    {
      pnt = add_block_end(size);
    }
  pthread_mutex_unlock(&list.mutex);
  return (pnt->pnt);
}

/**
* alloue nmemb * size octets de mémoire au système et "set" la mémoire allouée à zéro
* @param nmemb: le nombre d'éléments alloués, size: désigne la taille des éléments
* @return 
*/
void	  *calloc(size_t nmemb, size_t size)
{
  void	*pnt;

  if (nmemb * size == 0)
    return NULL;
  pnt = malloc(nmemb * size);
  memset(pnt, 0, nmemb * size);
  return pnt;
}

/**
* libère une zone mémoire précedemment allouée
* @param pnt_free: pointeur sur la zone mémoire à libérer
* @return void
*/
void		  free(void *pnt_free)
{
  t_block	*tmp;

  if (pnt_free == NULL)
    return;
  tmp = (t_block *)pnt_free - 1;
  if (tmp->pnt != pnt_free)
    return;
  pthread_mutex_lock(&list.mutex);
  tmp->free = true;
  fusion(&tmp);
  if (list.last->free == true)
  {
    if (list.last != list.beg)
  	{
  	  list.pnt_end_list = list.last;
  	  list.last->prev->next = NULL;
  	  list.last = list.last->prev;
  	}
  }
  deallocate_pageSize_memory();
  pthread_mutex_unlock(&list.mutex);
}

/**
* alloue une nouvelle zone mémoire de taille size et copie les éléments présents dans la zone mémoire pointée par pnt_re au début de la nouvelle zone allouée. La zone mémoire pointée par pnt_re est libérée et rendu au système
* @param pnt_re: pointeur sur la zone mémoire à realloc, size: taille de la nouvelle zone mémoire à allouer
* @return 
*/
void		  *realloc(void *pnt_re, size_t size)
{
  void		*pnt;
  t_block	*tmp;

  if (size == 0 && pnt_re != NULL)
    return (NULL);
  if (pnt_re == NULL)
    pnt = malloc(size);
  if (pnt_re != NULL)
    {
      tmp = (t_block *)pnt_re - 1;
      tmp->free = true;
      pnt = malloc(size);
      memcpy(pnt, pnt_re, tmp->size);
    }
  return pnt;
}

/**
* fonction pouvant être utilisée dans un programme tiers permettant d'avoir un rendu visuel de la mémoire
* @param void
* @return void
*/
void 		    show_alloc_mem()
{
  t_block 	*pnt = NULL;

  printf("break : %p\n", list.pnt_end_mem);
  pnt = list.beg;
  while (pnt != NULL)
  {
    if (pnt->free == false) printf("%p - %p : %lu octets\n", pnt->pnt, pnt->pnt + pnt->size, pnt->size);
    pnt = pnt->next;
  }
}
