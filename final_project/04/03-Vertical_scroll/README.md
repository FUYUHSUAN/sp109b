# 垂直滾動

在這裡我們可以順利地翻動我們所讀到的檔案

* 我們需要抓到屏幕的位置及文件的位置

```c
void editorScroll(){ //E.rowoff試紙屏幕頂部的內容
  if(E.cy < E.rowoff){//檢查光標是否在可見窗口上，如果是則向上滾動到光標所在位置上
    E.rowoff = E.cy;
  }
  if(E.cy >= E.rowoff + E.screenrows){ //是否越過可見窗口底部
    E.rowoff = E.cy - E.screenrows + 1;
  }
}
```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/04.aTextViewer.html)

