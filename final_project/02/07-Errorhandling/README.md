# 重建鍵盤輸入
* `if(nread == -1 && errno != EAGAIN) die("read");` : 沒有讀到，且錯誤不是沒有資料實惠印出錯誤訊息

* 在這段程式將原本的程式拆為兩個涵式去管理

* `editorReadKey()`:用來等待按鍵輸入，然後回傳值

* `editorProcessKeypress()` :判斷是否為Ctrl+w然後跳出
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

