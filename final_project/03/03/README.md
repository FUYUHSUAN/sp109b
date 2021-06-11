# Ctrl-W去停止此程式

kilo原本是使用Ctrl+Q去跳掉，但是VSCode會攔截事件，所以我使用Ctrl+Q去跳掉

* 這段程式是用來偵測輸入的Ctrl+我們指定的按鍵
    ```
    #define CTRL_KEY(k) ((k) & 0x1f)
    ```

* 這段式如果Ctrl+w時會跳出去
    ```
    if (c == CTRL_KEY('w')) break;
    ```

* 執行結果:一直輸出Null直到感受到Ctrl+w時結束，感受到其他案件時會知道是甚麼事件，然後輸出相對應的ASCII
```
root@localhost:~/sp109b/final_project/03/01# ./kilo
0
0
0
0
0
0
0
0
0
0
0
23
```
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

