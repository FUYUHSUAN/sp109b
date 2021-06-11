# 增加"~"在每一行

* 加上24行的開頭設為"~"的符號
    ```
    void editorDrawRows(){
        int y;
        for( y = 0; y < 24;y++){
            write(STDOUT_FILENO, "~\r\n", 3);
        }
    }
    ```
* `write(STDOUT_FILENO, "\x1b[2J", 4);`清除螢幕和迴滚緩衝區

* `write(STDOUT_FILENO, "\x1b[H", 3);` :定位移動光標的意思

* 輸出結果
    ```
    create mode 100644 final_project/03/04-Tildes/kilo.c 
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
    ```
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html)

