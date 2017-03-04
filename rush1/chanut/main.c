/*
** main.c for Semestre 1 in /home/guillaume1chanut/Semestre 1/Rush/rush1
**
** Made by chanut
** Login   <guillaume1chanut@epitech.net>
**
** Started on  Fri Mar 03 23:23:54 2017 chanut
** Last update Sat Mar 04 06:55:04 2017 chanut
*/

#include "my.h"
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

FILE*	create_archive(char **argv)
{
  FILE*	fichier;

  fichier = NULL;
  if ((fichier = fopen(argv[1], "w+")) == NULL)
    return (NULL);
  return (fichier);
}

t_posix		*fill_posix(char *path)
{
  int			fd;
  t_posix		*posix;
  struct stat		stats;
  struct group		*groupe;
  struct passwd		*user;
  char			str_uid[8];
  char			str_gid[8];
  char			str_size[12];
  char			str_link[100];
  char			str_time[12];
  char			str_mode[8];

  posix = malloc(sizeof(t_posix));
  memset(posix, 0, sizeof(t_posix));
  memset(&stats, 0, sizeof(stats));
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  fstat(fd, &stats);
  groupe = getgrgid(stats.st_gid);
  user = getpwuid(stats.st_uid);
  strncpy(posix->name, path, 100);
  sprintf(str_mode, "%d", stats.st_mode);
  strncpy(posix->mode, str_mode, 8);
  sprintf(str_uid, "%d", stats.st_uid);
  strncpy(posix->uid, str_uid, 8);
  sprintf(str_gid, "%ud", stats.st_gid);
  strncpy(posix->gid, str_gid, 8);
  sprintf(str_size, "%ld", stats.st_size);
  strncpy(posix->size, str_size, 12);
  sprintf(str_time, "%d", stats.st_mtim);
  strncpy(posix->mtime, str_time, 12);
  posix->typeflag = 'O';
  sprintf(str_link, "%ld", stats.st_nlink);
  strncpy(posix->linkname, str_link, 100);
  strncpy(posix->uname, user->pw_name, 32);
  strncpy(posix->gname, groupe->gr_name, 32);
  close(fd);
  return (posix);
}

void	fill_file_2(FILE* fichier, char *path)
{
  int	fd;
  char	*str;

  if ((fd = open(path, O_RDONLY)) != -1)
    {
      while ((str = get_next_line(fd)) != NULL)
	{
	  fputs(str, fichier);
	  fputc('\n', fichier);
  }
    }
  close(fd);
}
void	fill_file(FILE* fichier, t_posix *posix, char *path)
{
  int	fd;

  fd = 0;
  if ((fd = open(path, O_WRONLY)) < 1)
    exit(84);
  if ((write(fd, posix, sizeof(t_posix))) == -1)
    exit(84);
  printf("wesh\n");
  close(fd);
  fill_file_2(fichier, path);

}

int		main(int argc, char **argv)
{
  FILE*		fichier;
  t_posix	*posix = NULL;
  int	i;

  i = 2;
  fichier = NULL;
  if (argc == 1)
    {
      my_putstr("Usage: ./my_archive [archive_name] [files ...]");
      my_putchar('\n');
    }
  else
    {
      if ((fichier = create_archive(argv)) == NULL)
	return (84);
      while (i != argc)
	{
	  if ((posix = fill_posix(argv[i])) == NULL)
	      return (84);
	  fill_file(fichier, posix, argv[i]);
	  i = i + 1;
	}
    }
  return (0);
}