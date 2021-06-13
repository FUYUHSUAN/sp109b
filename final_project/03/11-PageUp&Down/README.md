# 增加PageUp&PageDown

這段程式執行時，能夠讓光標自由上下左右移動

* `strlen()` :來自<string.h>

* enum :列舉，一邊多用於只有少數值得類型
  ```c
  enum editprKey {  //在列舉中第一個設為1000，其他會依序設成1001,1002,1003
    ARROW_LEFT  = 1000,
    ARROW_RIGHT ,
    ARROW_UP ,
    ARROW_DOWN 
  };
  ```

---
* 運用上下左右鍵讓光標移動
  ```c
  void editorMoveCursor(int key){  //運用上下左右鍵讓光標移動
    switch(key) {
      case ARROW_LEFT:
        E.cx--;
        break;
      case ARROW_RIGHT:
        E.cx++;
        break;
      case ARROW_UP:
        E.cy--;
        break;
      case ARROW_DOWN:
        E.cy++;
        break;
    }
  }
  ```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html)

