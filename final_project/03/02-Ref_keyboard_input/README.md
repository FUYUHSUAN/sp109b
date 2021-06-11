# 重新建構鍵盤輸入

* 如果輸入失敗而且不是沒有輸入
    ```
    if (nread == -1 && errno != EAGAIN) die("read");
    ```
* 當讀到字元時，如果按下Ctrl+W就會離開
    ```
    void editorProcessKeypress() {
    char c = editorReadKey();
    switch (c) {
        case CTRL_KEY('q'):
        exit(0);
        break;
    }
    }
    ```

---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

