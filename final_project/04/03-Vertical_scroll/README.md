# 顯示多行

目前這個程式可以做到顯示多行但是還不能轉動他，當執行`/kilo kiloc`
  ```
  /*** includes ***/

  #define _DEFAULT_SOURCE
  #define _BSD_SOURCE
  #define _GNU_SOURCE

  #include <ctype.h>
  #include <errno.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/ioctl.h>
  #include <sys/types.h>
  #include <termios.h>
  #include <unistd.h>
  ```

* 主要改變178行的`E.numrows ++;`，讓他不再是只讀一行

* `while((linelen = getline(&line, &linecap, fp)) != -1)`  :這行是讀多行的關鍵，當他讀完這個檔案，getline()會回傳-1

* 其他我都註解在程式碼中，下一個會做到如何讓他滾動

---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/04.aTextViewer.html)

