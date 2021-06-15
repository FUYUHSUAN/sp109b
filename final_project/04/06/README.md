# 光標在最右邊時能自動換行，光標在最左邊時能自動回前一行


```c
void editorMoveCursor(int key) {
  erow *row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
  switch (key) {
    case ARROW_LEFT:
      if (E.cx != 0) {
        E.cx--;
      } else if (E.cy > 0) {
        E.cy--;
        E.cx = E.row[E.cy].size;
      }
      break;
    case ARROW_RIGHT:
      if (row && E.cx < row->size) {
        E.cx++;
      } else if (row && E.cx == row->size) {
        E.cy++;
        E.cx = 0;
      }
      break;
    case ARROW_UP:
      if (E.cy != 0) {
        E.cy--;
      }
      break;
    case ARROW_DOWN:
      if (E.cy < E.numrows) {
        E.cy++;
      }
      break;
  }
```

* 當到最右邊時會換行
  ```
  case ARROW_RIGHT:
        if (row && E.cx < row->size) {
          E.cx++;
        } else if (row && E.cx == row->size) {
          E.cy++;
          E.cx = 0;
        }
  ```

* 當道最左邊時會回到上一行
  ```
  case ARROW_LEFT:
      if (E.cx != 0) {
        E.cx--;
      } else if (E.cy > 0) {
        E.cy--;
        E.cx = E.row[E.cy].size;
      }
      break;
  ```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/04.aTextViewer.html)

