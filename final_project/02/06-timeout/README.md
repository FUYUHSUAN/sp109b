# 顯示鍵盤ASCII

輸出結果是一直印零，直到有輸入進去，也是一樣由q跳掉

* `make` : 先編譯

* VMIN 和 VTIME 是在<termios.h>中

* VMIN 是read()最少要該數量的字元才可讀取

* VTIME 是沒有輸入最少VMIN個字元會在VTIME後讀出





---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

