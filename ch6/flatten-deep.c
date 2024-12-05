#include <stdio.h>
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

struct wordscount *flatten_deep(struct tnode *p, struct wordscount *w) {
  if (p != NULL) {
    struct wordscount *left_w = flatten_deep(p->left, w);
    struct wordscount *wc = walloc();
    wc->count = p->count;
    wc->word = p->word;
    *left_w++ = *wc;

    struct wordscount *right_w = flatten_deep(p->right, left_w);
    return right_w;
  }
  return w;
}
