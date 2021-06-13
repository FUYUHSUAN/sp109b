# 顯示一行

目前編輯器只會顯示一行，我們在initEditor中初始化為零，其中numrows可以顯示0或1

  ```c
  //typedef允許我們將類型稱為erow而不是struct erow
  typedef struct erow {  //存除役行指向動態分配的長度與指針
    int size;
    char *chars;
  }erow;

  ```

  ```c
  void initEditor() {
    E.cx = 0;
    E.cy = 0;
    E.numrows = 0;
    if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
  }
  ```


---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html)

