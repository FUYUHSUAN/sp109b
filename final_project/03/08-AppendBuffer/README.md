# 增加緩衝區

* `realloc()`和`free()`都來自<stdlib.h>

* `realloc()`:給一個內存區，當前大小加上我們附加的字符串大小

* `memcpy()`來自<string.h>

* 我們使用`memcpy()`複製緩衝區中當前數據結束後的字符串s，並將abuf的指針和長度更新為新值。

* `abFree()` :用來釋放abuf使用的動態內存
  ```c
  void abAppend(struct abuf *ab, const char *s, int len) {
    char *new = realloc(ab->b, ab->len + len);

    if(new == NULL) return;
    memcpy(&new[ab->len], s, len);
    ab->b = new;
    ab->len += len;
  }

  void abFree(struct abuf *ab) {
    free(ab->b); //用來釋放abuf使用的動態內存
  }
  ```
---

* 用 `abAppend(&ab, ...)` 替換所有的`write(STDOUT_FILENO, ...)`
```c
void editorDrawRows(struct abuf *ab) {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    abAppend(ab, "~", 1);
    if (y < E.screenrows - 1) {
      abAppend(ab, "\r\n", 2);
    }
  }
}
void editorRefreshScreen() {
  struct abuf ab = ABUF_INIT;   //初始化名為ab的新abuf
  abAppend(&ab, "\x1b[2J", 4);
  abAppend(&ab, "\x1b[H", 3);
  editorDrawRows(&ab);
  abAppend(&ab, "\x1b[H", 3);
  write(STDOUT_FILENO, ab.b, ab.len); //最後將緩衝區的內容write()輸出到標準輸出
  abFree(&ab); //釋放abuf的內存
}
```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html)

