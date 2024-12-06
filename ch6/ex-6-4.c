#include "./flatten-deep.c"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD 100

char word[MAX_WORD];

/* qsort: sort v[left]...v[right] into increasing order */
void quick_sort(struct wordscount v[], int left, int right) {
  int i, last;
  void swap(struct wordscount v[], int i, int j);
  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (v[left].count < v[i].count)
      swap(v, ++last, i);
  swap(v, left, last);
  quick_sort(v, left, last - 1);
  quick_sort(v, last + 1, right);
}

void swap(struct wordscount v[], int i, int j) {
  struct wordscount temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
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
  if (!isalpha(c)) {
    *w = '\0';

    return c;
  }
  for (; --lim > 0; w++)
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
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

int main() {
  struct tnode *root = NULL;
  while (getword(word, MAX_WORD) != EOF) {
    if (isalpha(word[0])) {
      root = addtree(root, word);
    }
  }

  struct wordscount wordcounts[100000];
  struct wordscount *p_start = wordcounts;
  struct wordscount *p_end = flatten_deep(root, wordcounts);
  int wordscount_length = p_end - p_start;
  quick_sort(wordcounts, 0, wordscount_length - 1);
  for (int i = 0; i < wordscount_length; i++) {
    printf("%d %s\n", wordcounts[i].count, wordcounts[i].word);
  }

  return 0;
}
