# 增加訊息到我們的text editor中

* `snprintf()`來自<stdio.h>


* 在螢幕大小1/3的地方印我們想要給使用者看見的資訊
```c
void editorDrawRows(struct abuf *ab) {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    if(y == E.screenrows / 3){      //在螢幕大小1/3的地方印
      char welcome[80];
      int welcomelen = snprintf(welcome, sizeof(welcome), "Kilo editor -- version %s", KILO_VERSION);
      if(welcomelen > E.screencols) welcomelen = E.screencols;
      int padding = (E.screencols - welcomelen) / 2;
      if (padding) {
        abAppend(ab, "~", 1);
        padding--;
      }
      while (padding--) abAppend(ab, " ", 1);
      abAppend(ab, welcome, welcomelen);
    }else{
      abAppend(ab, "~", 1);
    }

    abAppend(ab, "\x1b[K", 3);
    if(y < E.screenrows - 1){
      abAppend(ab, "\r\n", 2);
    }  
  }
}

```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html)

