/*
** get_next_ligne.c for Semestre 1 in /home/guillaume1chanut/Semestre 1/Rush/rush1
**
** Made by chanut
** Login   <guillaume1chanut@epitech.net>
**
** Started on  Sat Mar 04 02:55:19 2017 chanut
** Last update Sat Mar 04 02:58:14 2017 chanut
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"my.h"

char		*my_realloc(char *array, int i)
{
  char		*str2;
  int		t;

  t = 0;
  str2 = malloc(sizeof(char) * i + 1);
  if (str2 == NULL)
    return (NULL);
  while (array[t] != '\0')
    {
      str2[t] = array[t];
      t++;
    }
  free (array);
  return (str2);
}

char	*reduce_size(char *str, int i, int *pointeur)
{
  str[i] = '\0';
  str = my_realloc(str, i + READ_SIZE);
  *pointeur = 0;
  return (str);
}

char	*norme(char *str, int i, int *a)
{
  str[i] = '\0';
  *a = *a - 1;
  return (str);
}

char		*get_next_line(const int fd)
{
  static int	pointeur = 0;
  static char	buffer[READ_SIZE];
  static int	a = 0;
  char		*str;
  int		i;

  i = 0;
  if ((str = malloc(sizeof(char) * READ_SIZE + 1)) == NULL)
    return (NULL);
  if (a == 0 && (a = read(fd, buffer, READ_SIZE)))
      pointeur = 0;
  if (a == -1 || a == 0)
    {
      a = 0;
      return (NULL);
    }
  while (buffer[pointeur] != '\n' && buffer[pointeur] != '\0')
    {
      str[i++] = buffer[pointeur++];
      if (--a == 0 && (a = read(fd, buffer, READ_SIZE)))
	str = reduce_size(str, i, &pointeur);
    }
  str = norme(str, i, &a);
  pointeur++;
  return (str);
}
