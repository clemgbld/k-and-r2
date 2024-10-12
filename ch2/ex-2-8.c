int rightrot(unsigned int x, unsigned int n) {
  int size = sizeof(x) * 8;
  return (x & ~(~0 << n)) << (size - n) | x >> n;
}
