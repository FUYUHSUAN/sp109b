# 回退格
因為到目前為止，只有插入的功能，所以接下來我會來實現為退格的部分

* 首先，先創建一個函數`editorRowDelChar()`

  ```c
  void editorRowDelChar(erow *row, int at) {
    if (at < 0 || at >= row->size) return;
    memmove(&row->chars[at], &row->chars[at + 1], row->size - at);  //複製後面的字元用來覆蓋前一個字元
    row->size--;
    editorUpdateRow(row);
    E.dirty++;   //dirty是用來看看是否有被修改的緩衝區，所以這被改過後，在緩衝區後加上1
  }

---
* 接下來實現editorDelChar()，它使用editoRowDelChar()山出光標左側的字符

  ```c
  void editorDelChar() {
    if (E.cy == E.numrows) return;  //如果光標越過文件末尾，則沒有要刪除的內容，我們立即返回
    erow *row = &E.row[E.cy];
    if (E.cx > 0) {
      editorRowDelChar(row, E.cx - 1);
      E.cx--;
    }
  }
---
* 接下來實現當回退鍵到達第一個字元時，會回退到上一行
  ```c
  void editorFreeRow(erow *row) {
    free(row->render);
    free(row->chars);
  }
  void editorDelRow(int at) {
    if (at < 0 || at >= E.numrows) return;
    editorFreeRow(&E.row[at]);
    memmove(&E.row[at], &E.row[at + 1], sizeof(erow) * (E.numrows - at - 1));
    E.numrows--;
    E.dirty++;
  }
---
* 接下來實現，讓他自符附加到一行的末端
  ```c
  void editorRowAppendString(erow *row, char *s, size_t len) {
    row->chars = realloc(row->chars, row->size + len + 1);
    memcpy(&row->chars[row->size], s, len);
    row->size += len;
    row->chars[row->size] = '\0';
    editorUpdateRow(row);
    E.dirty++;
  }

* 然後讓editorDelChar()處理行首的部分

  ```c
  void editorDelChar() {
    if (E.cy == E.numrows) return;
    if (E.cx == 0 && E.cy == 0) return;  //處理行首
    erow *row = &E.row[E.cy];
    if (E.cx > 0) {
      editorRowDelChar(row, E.cx - 1);
      E.cx--;
    } else {
      E.cx = E.row[E.cy - 1].size;
      editorRowAppendString(&E.row[E.cy - 1], row->chars, row->size);
      editorDelRow(E.cy);
      E.cy--;
    }
  }
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/05.aTextEditor.html)

