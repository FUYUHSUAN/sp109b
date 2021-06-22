# 實現Enter鍵的功能
允許按下Enter後將一行變成兩行的效果
* 在此我們先將`editorAppendRow(...)`替換成`editorInsertRow(E.numrows, ...)`，因此其他地方曾經使用過`editorAppendRow(...)`的地方我們都要將其替換
    ```c
    void editorInsertRow(int at, char *s, size_t len) {
    if (at < 0 || at > E.numrows) return;
    E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));
    memmove(&E.row[at + 1], &E.row[at], sizeof(erow) * (E.numrows - at));


    E.row[at].size = len;
    E.row[at].chars = malloc(len + 1);
    memcpy(E.row[at].chars, s, len);
    E.row[at].chars[len] = '\0';
    E.row[at].rsize = 0;
    E.row[at].render = NULL;
    editorUpdateRow(&E.row[at]);
    E.numrows++;
    E.dirty++;
    }
---
接下來，要實現Enter按鍵，在此我們增加了`editorInsertNewline()`
    ```c
    void editorInsertNewline() {
    if (E.cx == 0) { //如果我們要在一行的開頭時，我們所有做的就是，增加一個空白在其開頭
        editorInsertRow(E.cy, "", 0);  
    } else {
        erow *row = &E.row[E.cy];
        editorInsertRow(E.cy + 1, &row->chars[E.cx], row->size - E.cx);
        row = &E.row[E.cy];
        row->size = E.cx;
        row->chars[row->size] = '\0';
        editorUpdateRow(row);
    }
    E.cy++;
    E.cx = 0;
    }
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/05.aTextEditor.html)

