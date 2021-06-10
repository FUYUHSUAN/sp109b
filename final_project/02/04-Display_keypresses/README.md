# 顯示鍵盤

本程式是用來抓取控制字元與可顯示字元

* `make` : 先編譯

* 執行結果 `./kilo`
```
10       //ENTER(控制字元)
27       //ESC(控制字元)
79 ('O') //O(可顯示字元)
81 ('Q') 
116 ('t')
103 ('g')
```

* `iscntrl()` 是來自<ctype.h> :這是用來判斷這是否為一個控制字符，`iscntrl()`這個函數是如果是控制字符，會傳回一個非0值，否則回傳0
    * 控制字元 :ENTER,DEL,ESC...
    * 可顯示字元 :ASCII所包32~95的，例如!,1~9,f,e...



---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

