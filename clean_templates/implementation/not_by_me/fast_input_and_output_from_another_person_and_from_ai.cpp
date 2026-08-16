// input
inline int read() {
  int x = 0, s = 1;
  char c = getchar_unlocked();

  while (c < '0' || c > '9') {
    if (c == '-') s = -1;
    c = getchar_unlocked();
  }

  while (c >= '0' && c <= '9') {
    x = x * 10 + (c - '0');
    c = getchar_unlocked();
  }

  return x * s;
}
// for long long
inline long long readll() {
  long long x = 0;
  int s = 1;
  char c = getchar_unlocked();

  while (c < '0' || c > '9') {
    if (c == '-') s = -1;
    c = getchar_unlocked();
  }

  while (c >= '0' && c <= '9') {
    x = x * 10 + (c - '0');
    c = getchar_unlocked();
  }

  return x * s;
}

// output
// Avoid a recursive writer (stack overhead on many digits); use this
// iterative version instead.
inline void write(long long x) {
  if (x == 0) {
    putchar_unlocked('0');
    return;
  }

  if (x < 0) {
    putchar_unlocked('-');
    x = -x;
  }

  char s[20];
  int n = 0;

  while (x) {
    s[n++] = char('0' + x % 10);
    x /= 10;
  }

  while (n--) putchar_unlocked(s[n]);
}
