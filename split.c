/*
** split.c
** 
** Made by oleszkiewicz Jonathan
** Email   <JonathanOlesz@gmail.com>
** 
** Started on  Sun Feb 16 22:04:52 2014 oleszkiewicz
** Last update Sun Feb 16 22:16:04 2014 oleszkiewicz
*/

#include "malloc.h"

/**
* Crée un block de type t_block sur la zone mémoire désignée par pnt_on_split et relie ce nouveau block à la liste chainée. pnt désigne le bloc mémoire splité, nous allons donc créer un nouveau block à l'adresse mémoire indiquée par pnt_on_split et l'ajouter à notre liste chainée, ainsi ce block mémoire pourra être utilisé par malloc
* @param pnt: pointeur sur le maillon à spliter, pnt_on_split: pointeur sur la zone de splite (zone mémoire de création du nouveau bloc)
* @return void
*/
void	split_block(t_block *pnt, t_block *pnt_on_split)
{
  pnt_on_split->next = NULL;
  pnt_on_split->prev = NULL;
  pnt_on_split->free = true;
  pnt_on_split->pnt = (t_block *)pnt_on_split + 1;
  pnt_on_split->size = (void *)pnt->next - (void *)pnt_on_split->pnt;

  pnt->next->prev = pnt_on_split;
  pnt_on_split->next = pnt->next;
  pnt->next = pnt_on_split;
  pnt_on_split->prev = pnt;
}