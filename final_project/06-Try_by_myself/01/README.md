# 跳行功能
* 這個功能是參考kilo的網站並自行時做廚來的小功能，因為我覺得，有時編譯時，會顯示哪一行有問題，所以我加上了直接跳行的功能，就可以順利快速寫出我想要的程式

* 首先，先來創建一個`editorRowJump()`的函數
    ```c
    void editorRowJump(){
    char *query = editorPrompt("Jump to : %s");    //在最底下顯示我的提示訊息
    if (query == NULL) return;  
    if( atoi(query) > 0 && atoi(query) <=  E.numrows )  //搜尋的行數要大於0或是小於等於最大行數，才會進去做查詢的部分
        E.cy = atoi(query)-1;

    free(query);
    }
    ```

* 結果，就能順利的查詢了
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/05.aTextEditor.html)

