
int setbits(int x, int p, int n, int y) {
  return ((x | ~(~0 << n) << p) ^ ~(~0 << n) << p) | (y & ~(~0 << n)) << p;
}
