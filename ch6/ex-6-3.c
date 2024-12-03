#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10000

#define MAX_WORD 100

int current_line = 1;

const int NOISY_WORDS_LENGTH = 133;

char word[MAX_WORD];

char *noisy_words[] = {
    // Articles
    "the",
    "a",
    "an",
    // Conjunctions
    "and",
    "or",
    "but",
    "nor",
    "yet",
    "so",
    "for",
    // Prepositions
    "in",
    "on",
    "at",
    "to",
    "of",
    "by",
    "with",
    "about",
    "against",
    "between",
    "into",
    "through",
    "during",
    "before",
    "after",
    "above",
    "below",
    "from",
    "up",
    "down",
    "out",
    "over",
    "under",
    // Pronouns
    "I",
    "me",
    "my",
    "mine",
    "myself",
    "we",
    "us",
    "our",
    "ours",
    "ourselves",
    "you",
    "your",
    "yours",
    "yourself",
    "yourselves",
    "he",
    "him",
    "his",
    "himself",
    "she",
    "her",
    "hers",
    "herself",
    "it",
    "its",
    "itself",
    "they",
    "them",
    "their",
    "theirs",
    "themselves",
    // Auxiliary Verbs
    "is",
    "am",
    "are",
    "was",
    "were",
    "be",
    "being",
    "been",
    "have",
    "has",
    "had",
    "having",
    "do",
    "does",
    "did",
    "doing",
    "will",
    "would",
    "shall",
    "should",
    "can",
    "could",
    "may",
    "might",
    "must",
    // Adverbs
    "not",
    "no",
    "only",
    "now",
    "then",
    "there",
    "here",
    "very",
    "just",
    // Determiners and Quantifiers
    "this",
    "that",
    "these",
    "those",
    "each",
    "every",
    "either",
    "neither",
    "some",
    "any",
    "all",
    "many",
    "much",
    "more",
    "most",
    "few",
    "fewer",
    "several",
    "such",
    // Miscellaneous
    "how",
    "what",
    "which",
    "who",
    "whom",
    "whose",
    "why",
    "where",
    "when",
    "while",
    "if",
    "because",
    "than",
    "though",
    "although",
    "whether",
};

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
  if (c == '\n') {
    current_line++;
  }
  return c;
}
void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

struct tnode {
  char *word;
  int lines[MAX_LINES];
  int i;
  struct tnode *left;
  struct tnode *right;
};

/* talloc: make a tnode */
struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
  int cond;
  if (p == NULL) { /* a new word has arrived */
    p = talloc();  /* make a new node */
    p->word = strdup(w);
    p->i = 0;
    p->lines[0] = current_line;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    if (p->lines[p->i] != current_line) {
      p->i++;
      p->lines[p->i] = current_line;
    }
  } else if (cond < 0) /* less than into left subtree */
    p->left = addtree(p->left, w);
  else /* greater than into right subtree */
    p->right = addtree(p->right, w);
  return p;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, char *tab[], int n) {
  int cond;
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, tab[mid])) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%s\n", p->word);
    printf("LINES:\n");
    for (int i = 0; i <= p->i; i++) {
      printf("%d\n", p->lines[i]);
    }
    treeprint(p->right);
  }
}

int main() {
  struct tnode *root = NULL;
  while (getword(word, MAX_WORD) != EOF) {
    if (isalpha(word[0]) &&
        binsearch(word, noisy_words, NOISY_WORDS_LENGTH) < 0) {
      root = addtree(root, word);
    }
  }
  treeprint(root);
  return 0;
}
