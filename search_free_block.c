/*
** search_free_block.c
** 
** Made by oleszkiewicz Jonathan
** Email   <JonathanOlesz@gmail.com>
** 
** Started on  Sun Feb 16 22:04:52 2014 oleszkiewicz
** Last update Sun Feb 16 22:16:04 2014 oleszkiewicz
*/

#include "malloc.h"

/**
* recherche un block de données free de taille >= size + sizeof(t_block)
* @param size: taille de l'allocation mémoire demandée
* @return pointeur sur la sctucture de type t_block contenant les informations sur l'allocation mémoire
*/
t_block 		*free_block_higher_malloc_size(size_t size)
{
  t_block 	*pnt;

  pnt = list.beg;
  while (pnt != NULL && !(pnt->free == true && pnt->size >= size + sizeof(t_block)))
    pnt = pnt->next;
  return pnt;
}

/**
* recherche un block de données free de taille == size
* @param size: taille de l'allocation mémoire demandée
* @return pointeur sur la sctucture de type t_block contenant les informations sur l'allocation mémoire
*/
t_block    *free_block_equal_malloc_size(size_t size)
{
  t_block  *pnt;

  pnt = list.beg;
  while (pnt != NULL && !(pnt->free == true && pnt->size == size))
      pnt = pnt->next;
  return pnt;
}

/**
* recherche un block de données free de taille >= size
* @param size: taille de l'allocation mémoire demandée
* @return pointeur sur la sctucture de type t_block contenant les informations sur l'allocation mémoire
*/
t_block		*search_free_block(size_t size)
{
  t_block	*pnt;

  pnt = free_block_equal_malloc_size(size);
  if (pnt == NULL)
    pnt = free_block_higher_malloc_size(size);
  return pnt;
}
