#include "dirent.h"
#include <fcntl.h> /* flags for read and write */
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>  /* structure returned by stat */
#include <sys/types.h> /* typedefs */

void fsize(char *);
/* print file name */
int main(int argc, char **argv) {
  if (argc == 1) /* default: current directory */
    fsize(".");
  else
    while (--argc > 0)
      fsize(*++argv);
  return 0;
}

void dirwalk(char *, void (*fcn)(char *));
/* fsize: print the name of file "name" */
void fsize(char *name) {
  struct stat stbuf;
  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  {
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
      dirwalk(name, fsize);
    printf("%8lld %s\n", stbuf.st_size, name);
    printf("%d %s\n", stbuf.st_blksize, name);
    printf("%u %s\n", stbuf.st_mode, name);
    printf("%ld %s\n", stbuf.st_mtimespec.tv_nsec, name);
    printf("%ld %s\n", stbuf.st_mtimespec.tv_sec, name);
    printf("%d %s\n", stbuf.st_lspare, name);
    printf("%llu %s\n", stbuf.st_ino, name);
    printf("%u %s\n", stbuf.st_gid, name);
    printf("%lld %s\n", *stbuf.st_qspare, name);
    printf("%d %s\n", stbuf.st_nlink, name);
    printf("%d %s\n", stbuf.st_uid, name);
    printf("%d %s\n", stbuf.st_rdev, name);
    printf("%d %s\n", stbuf.st_flags, name);
    printf("%d %s\n", stbuf.st_gen, name);
  }
}

#define MAX_PATH 1024
/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *)) {

  char name[MAX_PATH];
  struct dirent *dp;
  DIR *dfd;
  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while ((dp = readdir(dfd)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, ".."))
      continue; /* skip self and parent */
    if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
      fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
    else {
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}
