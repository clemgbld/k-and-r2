#include "unistd.h"
#include <fcntl.h>
#include <stdlib.h>

#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

struct Fields {
  unsigned int _READ : 1;
  unsigned int _WRITE : 1;
  unsigned int _UNBUF : 1;
  unsigned int _EOF : 1;
  unsigned int _ERR : 1;
};
union Flag {
  struct Fields fields;
  unsigned int value;
};
typedef struct _iobuf {
  int cnt;         /* characters left */
  char *ptr;       /* next character position */
  char *base;      /* location of buffer */
  union Flag flag; /* mode of file access */
  int fd;          /* file descriptor */

} FILE;

extern FILE _iob[OPEN_MAX];
#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
#define feof(p) ((p)->flag.value) != 0)
#define ferror(p) ((p)->flag.fields._ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putcher(x) putc((x), stdout)

#define PERMS 0666 /* RW for owner, group, others */

FILE *fopen_custom(char *name, char *mode) {
  int fd;
  FILE *fp;
  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if (fp->flag.fields._READ == 0 && fp->flag.fields._WRITE == 0)
      break;                 /* found free slot */
  if (fp >= _iob + OPEN_MAX) /* no free slots */
    return NULL;
  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, O_RDONLY, 0);
  if (fd == -1) /* couldn't access name */
    return NULL;
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  if (*mode == 'r') {
    fp->flag.fields._READ = 1;
  } else {
    fp->flag.fields._WRITE = 1;
  }
  return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {
  int bufsize;
  if (fp->flag.fields._READ != 1 || fp->flag.fields._EOF == 1 ||
      fp->flag.fields._ERR == 1)
    return EOF;
  bufsize = fp->flag.fields._UNBUF == 1 ? 1 : BUFSIZ;
  if (fp->base == NULL) /* no buffer yet */
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF; /* can't get buffer */
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->flag.fields._EOF = 1;
    else
      fp->flag.fields._ERR = 1;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}
