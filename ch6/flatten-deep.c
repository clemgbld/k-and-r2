#include <stdlib.h>

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct wordscount {
  char *word;
  int count;
};

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

struct wordscount *walloc(void) {
  return (struct wordscount *)malloc(sizeof(struct wordscount));
}

void flatten_deep(struct tnode *p, struct wordscount *w) {
  struct wordscount *wc = walloc();
  wc->count = p->count;
  wc->word = p->word;
  *w++ = *wc;
}
