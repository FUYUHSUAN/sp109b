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

* `ftruncate()` and`close()` 來自 <unistd.h>.

    ```c
    void editorSave() {
    if (E.filename == NULL) return;
    int len;
    char *buf = editorRowsToString(&len);
    int fd = open(E.filename, O_RDWR | O_CREAT, 0644);
    ftruncate(fd, len);
    write(fd, buf, len);
    close(fd);
    free(buf);
    }
    ```
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/05.aTextEditor.html)

