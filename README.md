# The VIN Check

**O(n)**

The working code from the [@ByteAnimates](https://www.facebook.com/ByteAnimates) reel.

```bash
c++ -std=c++17 -O2 -o main main.cpp
./main
```

No dependencies. Any C++17 compiler.

### `vin.cpp`

```cpp
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
```

### Files

| | |
| --- | --- |
| `main.cpp` | build and run this — the demo, with real inputs and real output |
| `vin.cpp` | the reel snippet, generated from the episode |

---

The snippet above is generated from the video itself — what you read is byte-for-byte
what was typed on screen. A fix to it belongs in the episode, so open an issue and the
next reel carries it. Everything else here is hand-written and welcome as a pull request.
