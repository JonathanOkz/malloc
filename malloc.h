/*
** malloc.h
** 
** Made by oleszkiewicz Jonathan
** Email   <JonathanOlesz@gmail.com>
** 
** Started on  Sun Feb 16 22:13:56 2014 oleszkiewicz
** Last update Sun Feb 16 22:14:22 2014 oleszkiewicz
*/

#ifndef _MY_H
# define _MY_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef int bool;
#define true 1
#define false 0

typedef struct __attribute__((packed)) s_block {
  size_t                size; // taille en octet de la mémoire assignée au pointeur
  struct s_block        *next; // pointeur vers le maillon suivant de la liste chainée
  struct s_block        *prev; // pointeur vers le maillon précedent de la liste chainée
  bool                  free; // boolean, true: block free, false: block alloué
  void                  *pnt; // pointeur sur l'espace alloué
}t_block;

typedef struct __attribute__((packed)) s_list {
  t_block       	*beg; // pointeur sur le premier maillon de la liste chainée
  t_block       	*last; // pointeur sur le dernier maillon de la liste chainée
  void			      *pnt_end_list; // pointeur sur le dernier maillon de la liste chainée + sizeof(t_block) + size, renvoi l'adresse de la fin de la zone mémoire renvoyée par malloc
  void			      *pnt_end_mem; // pointeur sur la fin de la zone mémoire allouée par sbrk
  size_t		      sizePage; // taille du pagesize sur le système
  pthread_mutex_t	mutex;
}t_list;

t_list	list;


void    split_block(t_block *pnt, t_block *pnt_on_split);
t_block *search_free_block(size_t size);
void    deallocate_pageSize_memory();
void    allocate_pageSize_memory(size_t size);
void    initiation();
void    fusion(t_block **p);
void    *add(size_t size);
void    set_attribute_block(t_block *pnt, size_t size);
t_block *add_block_end(size_t size);

#endif
