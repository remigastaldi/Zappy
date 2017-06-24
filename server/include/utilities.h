/*
** utils.h for myirc
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Sun Jun 11 19:32:33 2017 Matthias Prost
** Last update Sat Jun 24 14:05:59 2017 Leo Hubert Froideval
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

typedef struct      s_action
{
    int             time;
    enum Action     action;
    t_users         *user;
    struct s_action *next;
    struct s_action *prev;
}                   t_action;

typedef struct      s_queue
{
    int             actions;
    t_action        *head;
    t_action        *end;
}                   t_queue;

char                *epurStr(char *);
char                *get_next_line(const int);
char                *myStrcpy(char *, char *);
char                *myStrdup(char *);
void                display_names(char **);
void                get_user(t_env *env, int fd, t_users *user);
void                print_map(t_env *env);
void                *xmalloc(size_t);
void                print_map(t_env *);

#endif /* !_UTILS_H_ */
