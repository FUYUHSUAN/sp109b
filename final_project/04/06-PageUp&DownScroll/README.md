# Page Up 和 Page Down的滾動 

我們現在有滾動的部分，所以我們將滾動添加到Page Up 和 Page Down，並將光標定位在頂部或底部去模擬上鍵和下鍵

* 其中` editorMoveCursor() `負責座移動時的邊境檢查

---
# 用END移到結尾


* 最主要就是改變`editorProcessKeypress()`
    ```c
        case END_KEY:
        if (E.cy < E.numrows)
            E.cx = E.row[E.cy].size;  //將E.cx移到row[E.cy](第幾行)的size(長度)
        break;
    ```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/04.aTextViewer.html)

