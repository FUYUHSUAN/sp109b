# 在最後一行也加上"~"


```
void editorDrawRows() {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    write(STDOUT_FILENO, "~", 1);
    if (y < E.screenrows - 1) {
      write(STDOUT_FILENO, "\r\n", 2);
    }
  }
}
```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html)

