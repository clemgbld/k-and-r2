
int isupper_save_memory(char c) { return (c >= 'A' && c <= 'Z'); }

int assci[128];

int isupper_save_time(int c) { return assci[c]; }

int main() {
  for (int i = 0; i < 128; i++) {
    if (i >= 'A' && i <= 'Z') {
      assci[i] = 1;
    } else {
      assci[i] = 0;
    }
  }
}
