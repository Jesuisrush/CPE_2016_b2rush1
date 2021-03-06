/*
** main.c for Semestre 1 in /home/guillaume1chanut/Semestre 1/Rush/rush1
**
** Made by chanut
** Login   <guillaume1chanut@epitech.net>
**
** Started on  Fri Mar 03 23:23:54 2017 chanut
** Last update Sat Mar 04 04:02:10 2017 chanut
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

t_posix			fill_posix(char *path)
{
  int			fd;
  t_posix		posix;
  struct stat		*stats;
  struct group		*groupe;
  struct passwd		*user;
  char			str_uid[8];
  char			str_gid[8];
  char			str_size[12];
  char			str_link[100];
  char			str_time[12];
  char			str_mode[8];

  stats = NULL;
  stats = malloc(sizeof(stat));
  if ((fd = open(path, O_RDONLY)) == -1)
    //return (NULL);
  fstat(fd, stats);
  groupe = getgrgid(stats->st_gid);
  user = getpwuid(stats->st_uid);
  strcpy(posix.name, path);
  sprintf(str_mode, "%d", stats->st_mode);
  strcpy(posix.mode, str_mode);
  sprintf(str_uid, "%d", stats->st_uid);
  strcpy(posix.uid, str_uid);
  sprintf(str_gid, "%ud", stats->st_gid);
  strcpy(posix.gid, str_gid);
  sprintf(str_size, "%ld", stats->st_size);
  strcpy(posix.size, str_size);
  sprintf(str_time, "%d", stats->st_mtim);
  strcpy(posix.mtime, str_time);
  posix.typeflag = 'O';
  sprintf(str_link, "%ld", stats->st_nlink);
  strcpy(posix.linkname, str_link);
  strcpy(posix.uname, user->pw_name);
  strcpy(posix.gname, groupe->gr_name);
  return (posix);
  memset(&posix, 0, sizeof(posix));
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
}

void	fill_file(FILE* fichier, t_posix posix, char *path)
{
  fputs(posix.name, fichier);
  fputs(posix.mode, fichier);
  fputs(posix.uid, fichier);
  fputs(posix.gid, fichier);
  fputs(posix.size, fichier);
  fputs(posix.mtime, fichier);
  fputc(posix.typeflag, fichier);
  fputs(posix.linkname, fichier);
  fputs(posix.uname, fichier);
  fputs(posix.gname, fichier);
  fill_file_2(fichier, path);
}

int		main(int argc, char **argv)
{
  FILE*		fichier;
  t_posix	posix;
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
	  posix = fill_posix(argv[i]);
	  fill_file(fichier, posix, argv[i]);
	  i = i + 1;
	}
    }
  return (0);
}
