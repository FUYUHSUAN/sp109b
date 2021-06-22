# 當未輸入任何文件名稱在./kilo 並將其另存為新的檔案

---
執行
* 此點程式，可以試著執行`./kilo`他就會出現空白文件
    ```
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    [No Name] - 1 lines (modified)                                 1/1HELP: Ctrl-S = save | Ctrl-Q = quit
    ```
* 接者，假設輸入一些東西並儲存(按下`Ctrl-S`)為test並按下Enter鍵跳出，在按下Ctrl-W就可以順利儲存他了
    ```
    wdefwe
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    ~
    [No Name] - 1 lines (modified)                                 1/1Save as: test (ESC to cancel)
    ```

* 在資料夾中就可看到剛剛我們所儲存的test
    ```
    root@localhost:~/sp109b/final_project/05/06# ls
    Makefile  README.md  kilo  kilo.c  test  
    ```
---
首先先創建一個`editorPrompt()`讓用戶在提示後輸入一行文本
    ```c
    char *editorPrompt(char *prompt) {
    size_t bufsize = 128;
    char *buf = malloc(bufsize);
    size_t buflen = 0;
    buf[0] = '\0';
    while (1) {
        editorSetStatusMessage(prompt, buf);
        editorRefreshScreen();
        int c = editorReadKey();
        if (c == '\r') {
        if (buflen != 0) {
            editorSetStatusMessage("");
            return buf;
        }
        } else if (!iscntrl(c) && c < 128) {
        if (buflen == bufsize - 1) {
            bufsize *= 2;
            buf = realloc(buf, bufsize);
        }
        buf[buflen++] = c;
        buf[buflen] = '\0';
        }
    }
    }
    ```

* 接下來，當這個名字沒出現過時就讓用戶輸入新名字
    ```c
    void editorSave() {
    if (E.filename == NULL) {
        E.filename = editorPrompt("Save as: %s");
    }
    ```

* 接下來，我們要能讓用戶按esc去取修儲存於是我們在`editorPrompt`中加上
    ```c
    if (c == '\x1b') {
        editorSetStatusMessage("");
        free(buf);
        return NULL;
        }
    ```

* 接下來要讓用戶可以按下`Backspace`或`Delete`因此我們在editorPrompt中加上
    ```c
    if (c == DEL_KEY || c == CTRL_KEY('h') || c == BACKSPACE) {
        if (buflen != 0) buf[--buflen] = '\0';
        }
    ```
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/05.aTextEditor.html)

