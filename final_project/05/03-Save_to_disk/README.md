# 儲存


* 首先先將每一行大小加1()儲存它的大小到並加一到`buflen`中，這是為了告訴調用者字符串有多長

* 接者，我們使用迴圈來看完整行，並用`memcpy()`將每行的內容到緩衝區，最後在每行結尾加上換行符號

* 最後返回buf，希望調用者釋放內存
    ```c
    char *editorRowsToString(int *buflen) {
    int totlen = 0;
    int j;
    for (j = 0; j < E.numrows; j++)
        totlen += E.row[j].size + 1;
    *buflen = totlen;
    char *buf = malloc(totlen);
    char *p = buf;
    for (j = 0; j < E.numrows; j++) {
        memcpy(p, E.row[j].chars, E.row[j].size);
        p += E.row[j].size;
        *p = '\n';
        p++;
    }
    return buf;
    }
    ```

---
* 接下來，我們會實現editorSave()函數，此函式會將 editorRowsToString() 返回的字符串寫入磁盤

* `open()`, `O_RDWR`, and `O_CREAT`來自<fcntl.h>

* `ftruncate()` and`close()` 來自 <unistd.h>


    ```c
    void editorSave() {
    if (E.filename == NULL) return;
    int len;
    char *buf = editorRowsToString(&len);
    int fd = open(E.filename, O_RDWR | O_CREAT, 0644);  //0644賦予文件使用者讀寫的功能，其他們只能讀取文件
    ftruncate(fd, len); //將文件設定為指定長度，如果文件太大，則則捨棄之後的數據，如果太短則在後端補0
    write(fd, buf, len);
    close(fd);
    free(buf);
    }
    ```

---
接者製作Ctrl + S鍵去做保存，在editorProcessKeypress()中增加以下程式來儲存
    ```c
    case CTRL_KEY('s'):
        editorSave();
        break;
    
---
接下來，使用`editorSetStatusMessage("%d bytes written to disk", len);` 確認儲存是否成功

* 在int main中加入`editorSetStatusMessage("HELP: Ctrl-S = save | Ctrl-W = quit");`來提醒使用者

---
接來做提醒使用者當他們修改

* 如果文件已被修改，通過文件名後顯示修改，
再狀態欄中顯示E.dirty

    ```c
    void editorDrawStatusBar(struct abuf *ab) {
    abAppend(ab, "\x1b[7m", 4);
    char status[80], rstatus[80];
    int len = snprintf(status, sizeof(status), "%.20s - %d lines %s",
        E.filename ? E.filename : "[No Name]", E.numrows,
        E.dirty ? "(modified)" : "");
    int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d",
        E.cy + 1, E.numrows);
    if (len > E.screencols) len = E.screencols;
    abAppend(ab, status, len);
    while (len < E.screencols) {
        if (E.screencols - len == rlen) {
        abAppend(ab, rstatus, rlen);
        break;
        } else {
        abAppend(ab, " ", 1);
        len++;
        }
    }
    abAppend(ab, "\x1b[m", 3);
    abAppend(ab, "\r\n", 2);
    }

    ```
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/05.aTextEditor.html)

