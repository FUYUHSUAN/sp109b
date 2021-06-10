# 讀取指令

讀到字元`'q'`時離開

* `make` : 先編譯

* `read()` 和 `STDIN_FILENO` 是來自 <unistd.h>

* 整段程式碼
    ```c
    #include <unistd.h>

    int main(){
        char c;
        while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
        return 0; 
    }
    ```

    * `read(STDIN_FILENO, &c, 1) == 1` **:** 一次讀一個字元直到沒有字元可以讀為止，read() 成功讀取時會回傳1

    * `while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');` **:** 他有讀到字元，且讀到的字元不是q時會持續執行，也就是說讀到q時會離開

    * 此處的 `return 0` 就是當它讀完整個檔案時，就會回傳0

---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

