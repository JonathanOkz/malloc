/*
** add_memory_block.c
** 
** Made by oleszkiewicz Jonathan
** Email   <JonathanOlesz@gmail.com>
** 
** Started on  Sun Feb 16 22:04:52 2014 oleszkiewicz
** Last update Sun Feb 16 22:16:04 2014 oleszkiewicz
*/

#include "malloc.h"

/**
* crée un maillon à la fin de la liste chainée
* @param size: taille de l'allocation mémoire demandée
* @return pointeur sur la sctucture de type t_block contenant les informations sur l'allocation mémoire
*/
t_block   *create_block_end(size_t size)
{
  t_block *pnt;

  pnt  = (t_block *)list.pnt_end_list;
  pnt->next = NULL;
  pnt->prev = NULL;
  pnt->size = size;
  pnt->free = false;
  pnt->pnt = pnt + 1;
  if (list.beg == NULL)
    {
      list.beg = pnt;
      list.last = pnt;
    }
  else
    {
      list.last->next = pnt;
      pnt->prev = list.last;
      list.last = pnt;
    }
  return pnt;
}

/**
* ajoute un block de données à la fin de la liste chainée, demande plus de moimoire si nésésire et décale le pointeur list.pnt_end_list à la fin de l'allocation memoire
* @param size: taille de l'allocation memoire demandé
* @return poiteur sur la sctucture de type t_block contenant les information sur l'allocation memoire
*/
t_block   *add_block_end(size_t size)
{
  t_block *pnt;

  allocate_pageSize_memory(size);
  pnt = create_block_end(size);
  list.pnt_end_list += sizeof(t_block) + size;
  return pnt;
}

/**
* Si pnt désigne le dernier block de la lite chainée, on assigne le pointeur list.pnt_end_list à la valeur de pnt + sizeof(t_block) + size, ainsi list.pnt_end_list désigne la fin de la zone mémoire rendu disponible par malloc. La zone mémoire contenu entre list.pnt_end_list et list.pnt_end_mem sera rendu au system par plage de pagesize
* Si pnt->size == size c'est que malloc réutilise un block existant, on set ça valeur free à false pour sinifier que le block est occupé
* Si pnt->size >= size + sizeof(t_block) c'est que malloc va utiliser une partie d'un bock exitant, il faudra donc le spliter pour rendre la partie non utilisé disponnible à une prichaine utilisation, la fonction split_block() scindra le block en 2, le paramétre free du premier block sera setté à false et celui du deuxème à true
* @param t_block: poiteur du le bock, size: taille de l'allocation memoire demandé
* @return void
*/
void	set_attribute_block(t_block *pnt, size_t size)
{
  if (pnt == list.last && pnt->next == NULL)
    {
      list.pnt_end_list = pnt->pnt + size;
      pnt->free = false;
      pnt->size = size;
    }
  else if (pnt->size == size)
    {
      pnt->free = false;
    }
  else if (pnt->size >= size + sizeof(t_block))
    {
      split_block(pnt, (t_block *)(pnt->pnt + size));
      pnt->size = size;
      pnt->free = false;
    }
}
