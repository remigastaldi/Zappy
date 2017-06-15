/*
** utils.h for myirc
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Sun Jun 11 19:32:33 2017 Matthias Prost
** Last update	Thu Jun 15 15:13:58 2017 Full Name
*/

#ifndef _UTILS_H_
#define _UTILS_H_

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

typedef struct sockaddr		SOCKADDR;
typedef struct sockaddr_in	SOCKADDR_IN;

char				*epurStr(char *str);
char				*get_next_line(const int fd);
char				*end(char *ret, int *tab, int *nb);
char				*verif(char *ret, int *tab, int *nb, char *buff);
char				*myRealloc(char *ret, int *tab, int *nb, char *buff);
char				*initialisation(char *ret, int *tab, int *nb, char *buff);
void				freeTab(char **tab);
int				myCount(char *str, char c);
char				**toWordtab(char *str, char c);
int				lenTab(const char *str, char c);
char				*myStrdup(char *s);
char				*myStrcpy(char *dest, char *src);
char				*myStrcat(char *s1, char *s2, char deli, int toFree);

#endif /* !_UTILS_H_ */
