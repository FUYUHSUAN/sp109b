# 插入基本的字元
先嘗試插入單一字元到erow中，並得到位置(目前這段只是單純可以插入文字)

* `memmove()` 來自 <string.h>
  * `void * mommove(void *str1, const void *str2, size_t n`: 複製n個字符從str2到str1

* 首先先驗證at，這是要插入的索引。我們會允許at超出字符串末尾字符，用來插入於字符的尾端
  ```c
  void editorRowInsertChar(erow *row, int at, int c){
    if(at < 0 || at > row->size) at = row->size;
    row->chars = reallco(row->chars, row->size + 2); //+2是因為我們要為空字元騰出空間 
    memmove(&row->chars[at + 1], &row->chars[at], row->size - at + 1);  //用memmove為新字符騰出空間
    row->size++;
    row->chars[at] = c;
    editorUpdateRow(row);  //使用新航的內容更新和rsize字段
  }
  ```

* 添加一個名為 `editorInsertChar()` 的函數，該函數將接受一個字符並使用 `editorRowInsertChar()` 將該字符插入到光標所在的位置

  ```c
  void editorInsertChar(int c) {
    if (E.cy == E.numrows) {
      editorAppendRow("", 0);
    }
    editorRowInsertChar(&E.row[E.cy], E.cx, c);
    E.cx++;
  }
  ```

* 補充: editorInsertChar() 不必擔心修改行的細節， editorRowInsertChar() 不必擔心光標在哪裡。這就是 `/*** editor operations ***/ `部分中的函數與` /*** row operations ***/` 部分中的函數之間的區別。

* 接者，在`editorProcessKeypress()`中插入以下程式碼
```c
default:
      editorInsertChar(c);
      break;
```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/05.aTextEditor.html)

