int binsearch(int x, int v[], int n) {
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid]) {
      high = mid + 1;
    } else {
      low = mid + 1;
    };
  }
  return x == v[mid] ? mid : -1;
}
