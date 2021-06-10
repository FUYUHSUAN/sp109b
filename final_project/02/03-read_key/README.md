# 關閉RawMode

本程式會一次讀一個字元，然後讀到q時會跳出去

* 在linux中要掌控一切才能做出vim，所以要能控制到每個鍵盤，每個字元的輸入

* `make` : 先編譯

* `ICANON` :這表示canonical mode模式，的意思是具能有特殊自元功能，例如EOF, EOL, EOL2...
    * 因此在這段程式中我們關閉這個功能 ，使用 `raw.c_lflag &= ~(ECHO | ICANON);` 來將其設為diable

* 以下這段程式用來關閉Rawmode的功能
    ```
    void disableRawMode(){
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }
    ```

---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

