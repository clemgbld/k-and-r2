#include "./take-first.c"
#include <_ctype.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode_group {
  char *word;
  struct tnode *group;
  struct tnode_group *left;
  struct tnode_group *right;
};

struct tnode *talloc(void);
struct tnode_group *tgroupalloc(void);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
  int cond;
  if (p == NULL) { /* a new word has arrived */
    p = talloc();  /* make a new node */
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;      /* repeated word */
  else if (cond < 0) /* less than into left subtree */
    p->left = addtree(p->left, w);
  else /* greater than into right subtree */
    p->right = addtree(p->right, w);
  return p;
}

struct tnode_group *addtree_group(struct tnode_group *p, char *w, int slice) {
  char *word = take_first(w, slice);
  int cond;
  if (p == NULL) {
    p = tgroupalloc();
    p->word = strdup(word);
    p->group = addtree(NULL, w);
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word))) {
    p->group = addtree(p->group, w);
  } else if (cond > 0) {
    p->left = addtree_group(p->left, w, slice);
  } else {
    p->right = addtree_group(p->right, w, slice);
  }
  free(word);
  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

void tree_group_print(struct tnode_group *p) {
  if (p != NULL) {
    tree_group_print(p->left);
    printf("GROUP OF VARIABLES NAMES: %s\n", p->word);
    treeprint(p->group);
    tree_group_print(p->right);
  }
}

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

struct tnode_group *tgroupalloc(void) {
  return (struct tnode_group *)malloc(sizeof(struct tnode_group));
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  while (isspace(c = getch()))
    ;

  if (c != EOF)
    *w++ = c;

  if (!isalpha(c) && c != '"' && c != '#' && c != '/') {
    *w = '\0';
    return c;
  }

  int isStringConstant = c == '"';

  int isPreprocessor = c == '#';

  int isPotentialComment = c == '/';

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
      *w = getch();
      if (*w == '\n') {
        break;
      }
    }

  } else if (isPotentialComment) {
    int next;
    if (--lim > 0) {
      int next = getch();
      if (next == '/') {
        *w++ = '/';
        for (; --lim > 0 && (*w++ = getch()) != '\n';)
          ;
      } else if (next == '*') {
        *w++ = '*';
        int end;
        for (; --lim > 0 && (end = getch()) != EOF;) {
          *w++ = end;
          if (end == '*') {
            int nextEnd = getch();
            if (nextEnd == '/') {
              *w++ = nextEnd;
              break;
            } else {
              ungetch(nextEnd);
            }
          }
        }
      }
    } else {
      ungetch(next);
      *w = '\0';
      return c;
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

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */
int getch(void)    /* get a (possibly pushed-back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

int main(int argc, char **argv) {
  int n;
  if (argc == 2) {
    char *n_str = argv[1];

    if (*n_str++ != '-') {
      printf(
          "%s wrong format, every command line argument should start with - \n",
          n_str);
      return 1;
    }

    if (isnumber(*n_str)) {
      n = atoi(n_str);
    } else {
      printf("%s should be a number \n", n_str);
      return 1;
    }
  } else {
    printf("Too many arguments or too feew arguments should only have one "
           "argument\n");
    return 1;
  }

  struct tnode_group *root = NULL;
  char word[MAXWORD];
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      root = addtree_group(root, word, n);
    }
  }
  tree_group_print(root);
  return 0;
}
