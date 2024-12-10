#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {        /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
  struct nlist *np;
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; /* found */
  return NULL;   /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;
  if ((np = lookup(name)) == NULL) { /* not found */
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else                    /* already there */
    free((void *)np->defn); /*free previous defn */
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */
int getch(void)    /* get a (possibly pushed-back) character */
{
  if (bufp > 0)
    return buf[--bufp];
  int c = getchar();
  return c;
}
void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  while (isspace(c = getch())) {
    putchar(c);
  }

  if (c != EOF)
    *w++ = c;

  if (!isalnum(c) && c != '"' && c != '#') {
    *w = '\0';
    return c;
  }

  int isStringConstant = c == '"';

  int isPreprocessor = c == '#';

  if (isStringConstant) {
    int prev = *w;
    for (; --lim > 0; w++) {
      *w = getch();
      if (*w == '"' && prev != '\\') {
        w++;
        break;
      }
      prev = *w;
    }

  } else if (isPreprocessor) {
    for (; --lim > 0; w++) {
      char temp = getch();
      if (isspace(temp)) {
        ungetch(temp);
        break;
      }
      *w = temp;
    }

  } else {
    for (; --lim > 0; w++)
      if (!isalnum(*w = getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
  }

  *w = '\0';
  return word[0];
}

void putchars(char *w) {
  while (*w != '\0') {
    putchar(*w);
    w++;
  }
}

#define WORD 100

int main() {
  bool shouldCaptureNextName = false;
  bool shouldInstallDefine = false;
  int c;

  char word[100];
  char name[100];
  while ((c = getword(word, WORD)) != EOF) {
    if (strcmp(word, "") == 0) {
      putchar(c);
      continue;
    } else if (shouldInstallDefine) {
      putchars(word);
      install(name, word);
      shouldInstallDefine = false;
    } else if (shouldCaptureNextName) {
      putchars(word);
      strcpy(name, word);
      shouldCaptureNextName = false;
      shouldInstallDefine = true;
    } else if (lookup(word) != NULL) {
      char *w = lookup(word)->defn;
      putchars(w);
    } else if (strcmp(word, "#define") == 0) {
      putchars(word);
      shouldCaptureNextName = true;
    } else {
      putchars(word);
    }
  }
}
