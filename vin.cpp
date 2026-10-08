// The VIN Check — O(n)
// As shown in the reel
// Generated from the episode; edits here are overwritten. See the README.

int val(char c) {
  if (c <= '9') return c - '0';
  int k = c - 'A' + (c >= 'S');
  return k % 9 + 1;
}
char check(const char* v) {
  int w[] = {8,7,6,5,4,3,2,10,0,9,
    8,7,6,5,4,3,2}, s = 0;
  for (int i = 0; i < 17; i++)
    s += val(v[i]) * w[i];
  return "0123456789X"[s % 11];
}
