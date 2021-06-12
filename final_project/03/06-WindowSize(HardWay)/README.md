# 了解Window 大小

首先需要一個存取中端的寬度與高度，

* `struct termios orig_termios;` : 用來存取終端的寬度與高度，放入結構體中，接者我們運用全域變數E，使用E.orig_termios來替換所有的orig_termios

---

接者我們會使用TIOCGWINSZ來請求ioctl()來獲得終端的大小

* `ioctl()`,`TIOCGWINSZ`和`struct winsize`都來自<sys/ioctl.h>

* 如果失敗ioctl()會return -1並讓getWindowSize()報失敗

```c
int getWindowSize(int *rows, int *cols) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) { //如果ioctl()會將終端的特定的行樹和列寬放入給定的winsize結構中
    return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}
```
---
接下來設立兩個全域編輯器狀態，來填充getWindowSize()

* 我們設置initEditor()來初始化E結構中的所有字段

```
void initEditor(){
	if(getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}

```
---
接者就是設置正確數量的的波浪("~")到我們螢幕上

```
void editorDrawRows() {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}
```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html)

