/*
** tools.c for Semestre 1 in /home/guillaume1chanut/Semestre 1/Rush/rush1
**
** Made by chanut
** Login   <guillaume1chanut@epitech.net>
**
** Started on  Fri Mar 03 23:32:20 2017 chanut
** Last update Fri Mar 03 23:33:56 2017 chanut
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\n' && str[i] != '\0')
    {
      my_putchar(str[i]);
      i = i + 1;
    }
}
