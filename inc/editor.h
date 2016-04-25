/*
** editor.h for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/includes/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Mon Apr 25 04:09:19 2016 Ethan Kerdelhue
** Last update Mon Apr 25 06:25:00 2016 Ethan Kerdelhue
*/

#ifndef			EDITOR_H_
# define		EDITOR_H_

# include		"main.h"

# define		ERR_NOCMD		-1
# define 		ERR_NOACC		-2
# define		ERR_NOSTR		-3

typedef struct s_cmd
{
  char		*index;
  char		*desc;
  int 		(*ptr)(t_prog *);
}		t_cmd;

void			editor(void);

#endif		      /*EDITOR_H_*/
