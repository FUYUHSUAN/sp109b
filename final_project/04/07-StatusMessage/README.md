# 消息狀態

* 首先先用來儲存現階段的訊息，接者，給一個時間戳來擦除過一段時間後的訊息

  * time_t comes 來自 <time.h>.
  ```c
  struct editorConfig {  //用來存取終端的寬度與高度
  int cx, cy;  //初始化cx和cy用來來追蹤cursor的位置
  int rx;
  int rowoff;  //跟蹤用戶當前滾動到文件的幾行
  int coloff; //列(水平)位移變量
  int screenrows;
  int screencols;
  int numrows;
  erow *row;  //為了儲存多行，因此將row設為一個指針
  char *filename;
  char statusmsg[80];  //用來儲存現階段的訊息
  time_t statusmsg_time;   //增加時間戳，可以在幾秒鐘後將訊息刪除
  struct termios orig_termios;
};


* 並將E.statusmsg初始化為空字串，因此默認情控下不會顯示任何消息

* E.statusmsg_time 包含我們設置消息狀態時的時間戳
  ```
  void initEditor() { //設置initEditor()來初始化E結構中的所有字段
    
    //設定cursor一開始的位置在(0,0)的位置
    E.cx = 0; 
    E.cy = 0;
    E.rx = 0;
    E.rowoff = 0; //初始化為0，默認滾動到文件頂部
    E.coloff = 0;
    E.numrows = 0;
    E.row = NULL;
    E.filename = NULL;
    E.statusmsg[0] = '\0';  //初始化為空字串，因此默認情控下不會顯示任何消息
    E.statusmsg_time = 0;   //包含我們設置消息狀態時的時間戳

  ```
---
* `va_list`, `va_start()`, and `va_end()`來自<stdarg.h>，此標準函式庫主要目的是讓函式能夠接收不定量參數

* `vsnprintf()` 來自 <stdio.h>

* `...` : 表示 `editorSetStatusMessage`成為可變參數，他可以接受任意數量的參數

  ```c
  void editorSetStatusMessage(count char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap); //vsnprintf幫助我們製作自己的printf()風格函數，並將結果字符串儲存至E.statusmsg 中
    va_end(ap);
    E.statusmsg_time = time(NULL); //將 E.statusmsg_time 設置為當前時間，可以通過將 NULL 傳遞給 time() 來獲取
  }
  ```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/04.aTextViewer.html)

