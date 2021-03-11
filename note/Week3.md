## 從lexer --> 編譯器(if/while...)
>* 02-lexer(其中lexer.c為主要程式，sum.c為測試用的)
* lexer : 變成一個個token(字串)，然後將其一個一個讀出來
* 指標複習:

<img src="picture/pointer1.png">

<img src="picture/pointerbug.png">

* 編譯程式: gcc lexer.c -o lexer
* 執行程式: ./lexer sum.c
* 執行結果:  
```
#include "sum.h"

int main() {
  int t = sum(10);
  printf("sum(10)=%d\n", t);
}
token=#      
token=include
token="sum.h"
token=int    
token=main   
token=(
token=)
token={
token=int
token=t
token==
token=sum
token=(
token=10
token=)
token=;
token=printf
token=(
token="sum(10)=%d\n"
token=,
token=t
token=)
token=;
token=}
0:#
1:include
2:"sum.h"
3:int
4:main
5:(
6:)
7:{
8:int
9:t
10:=
11:sum
12:(
13:10
14:)
15:;
16:printf
17:(
18:"sum(10)=%d\n"
19:,
20:t
21:)
22:;
23:}
```
```
int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}
// rw+:既可以讀取又可以寫入，如果當按不存在則新增
// r:只讀取
// w:創造一個空黨，如廣檔案存在，原本的會被清空
// w+:先清空，既可以讀又可以寫
// r+:既可讀又可以寫
// wb:2進位的讀檔
```