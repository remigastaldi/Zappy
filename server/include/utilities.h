/*
** utils.h for myirc
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Sun Jun 11 19:32:33 2017 Matthias Prost
** Last update Fri Jun 23 16:18:59 2017 Leo Hubert Froideval
*/

#ifndef _UTILS_H_
#define _UTILS_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#define READ_SIZE		14
#define MAX_FD			255

typedef void(*fct)();

typedef struct sockaddr		SOCKADDR;
typedef struct sockaddr_in	SOCKADDR_IN;

typedef enum        Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
}                   Direction;

typedef enum        Action
{
    LOOK,

}                   Action;

typedef struct      s_items
{
    int             linemate;
    int             deraumere;
    int             sibur;
    int             mendiane;
    int             phiras;
    int             thystame;
}                   t_items;

typedef struct	    s_users
{
  int				socket;
  int               posY;
  int               posX;
  int               lvl;
  char              *teamName;
  Direction         direction;
}				    t_users;

typedef struct		s_env
{
  int				port;
  int               width;
  int               height;
  t_items           **map;
  int               nbrRessources;
  char              **names;
  int               clientsNb;
  int               freq;
  t_users		    users[MAX_FD];
  char			    fd_type[MAX_FD];
  fct				fct_read[MAX_FD];
  fct				fct_write[MAX_FD];
}				    t_env;

typedef struct      s_instruction
{
    int             time;
    enum Action     action;
    t_users         *user;
}                   t_instruction;

char				*epurStr(char *str);
char				*get_next_line(const int fd);
char      	*myStrcpy(char *dest, char *src);
char  			*myStrdup(char *s);
void        display_names(char **tab);
void        *xmalloc(size_t);
void        print_map(t_env *env);
void        get_user(t_env *env, int fd, t_users *user);

char                *epurStr(char *str);
char                *get_next_line(const int fd);
char                *myStrcpy(char *dest, char *src);
char                *myStrdup(char *s);
void                display_names(char **tab);
void                *xmalloc(size_t);
void                print_map(t_env *env);

#endif /* !_UTILS_H_ */
