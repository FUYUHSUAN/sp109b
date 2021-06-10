# 關閉覆讀功能

本程式輸入時看不到任何輸入，但是會聽得見任何我們打的指令，按下Ctrl+C或是打上reset可以跳出來

* `make` : 先編譯

* `struct termios` , `tcgetattr()` , `tcsetattr()` , `ECHO` 和 `TCSAFLUSH`  是來自 <termios.h>

* 整段程式碼
    ```c
    #include <termios.h>
    #include <unistd.h>

    void enableRawMode(){
        struct termios raw; 

        tcgetattr(STDIN_FILENO, &raw);

        raw.c_lflag &= ~(ECHO);

        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }
    int main(){
        enableRawMode();

        char c;
        while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
        return 0;
    }

    ```

    * `tcgetattr` 和 `tcsetattr` **:** 是linux用來控制終端

    * `raw.c_lflag &= ~(ECHO);` **:** 將ECHO設為disable，其中ECHO是用來顯示字元

    * `TCSAFLUSH` **:** 清空輸入輸出緩衝區才改變屬性
    



---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

