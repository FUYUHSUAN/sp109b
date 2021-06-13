# 顯示多行

現在執行`./kilo kilo.c`會顯示多行，但是還不能滾動
* 執行結果:

    ```
    root@localhost:~/sp109b/final_project/04# ./kilo kilo.c/*** includes ***/

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

* `erow *row; `:為了儲存多行，因此將row設為一個指針

* `while((linelen = getline(&line, &linecap, fp)) != -1)` :這行是讀多行的關鍵，當他讀完這個檔案，getline()會回傳-1

* 其他的細節解釋，我都註解於程式碼中
    ---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/04.aTextViewer.html)

