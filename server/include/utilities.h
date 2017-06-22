/*
** utils.h for myirc
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Sun Jun 11 19:32:33 2017 Matthias Prost
** Last update Thu Jun 22 16:24:44 2017 Leo Hubert Froideval
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

typedef struct sockaddr		SOCKADDR;
typedef struct sockaddr_in	SOCKADDR_IN;

char				*epurStr(char *str);
char				*get_next_line(const int fd);
char      	*myStrcpy(char *dest, char *src);
char  			*myStrdup(char *s);
void        display_names(char **tab);
void        *xmalloc(size_t);

#endif /* !_UTILS_H_ */
