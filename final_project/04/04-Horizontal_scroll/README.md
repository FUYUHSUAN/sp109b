# 水平滾動

我們接下來做水平滾動，我們先加上`coloff`變量在editorConfig，這邊改的東西實際上跟垂直滾動差不多

```c
void editorScroll(){ //E.rowoff試紙屏幕頂部的內容
  if(E.cy < E.rowoff){//檢查光標是否在可見窗口上，如果是則向上滾動到光標所在位置上
    E.rowoff = E.cy;
  }
  if(E.cy >= E.rowoff + E.screenrows){ //是否越過可見窗口底部
    E.rowoff = E.cy - E.screenrows + 1;
  }

  if(E.cx < E.coloff){
    E.coloff = E.cx;
  }
  if(E.cx >= E.coloff + E.screencols){
    E.coloff = E.cx - E.screencols + 1;
  }
}

```

---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/04.aTextViewer.html)

