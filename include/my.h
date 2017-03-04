/*
** my.h for Semestre 1 in /home/guillaume1chanut/Semestre 1/Rush/rush1/include
**
** Made by chanut
** Login   <guillaume1chanut@epitech.net>
**
** Started on  Fri Mar 03 23:34:18 2017 chanut
** Last update Sat Mar 04 03:06:06 2017 chanut
*/

#ifndef s_posix
# define s_posix

typedef struct s_posix
{
  char	name[100];
  char	mode[8];
  char	uid[8];
  char	gid[8];
  char	size[12];
  char	mtime[12];
  char	chksum[8];
  char	typeflag;
  char	linkname[100];
  char	magic[6];
  char	version[2];
  char	uname[32];
  char	gname[32];
  char	devmajor[8];
  char	devminor[8];
  char	prefix[155];
}		t_posix;

#endif /* !s_posix */

#ifndef MY_H_
# define MY_H_

void	my_putchar(char c);
void	my_putstr(char *str);
char	*get_next_line(const int fd);

#endif /* MY_H_ */

# ifndef	READ_SIZE
#  define	READ_SIZE 10
# endif /* !READ_SIZE */
