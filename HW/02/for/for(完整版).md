### for較完整版
* 這一版的，我放在compiler2.c，因此Makefile中，也做了改變
>* 上一次for.md那一個版本，因為會堤早加加，所以會出現問題，所以這一次的版本宿改了這個問題
>* 首先在define emit printf 那邊做點修改，我們有預設一個public的int isTempIr，這個是用來判斷當如果isTempIr是1的話我們就不會印出來，而且我們將其變成一個指標陣列tempIrp存起來
```
char tempIr[100000], *tempIrp = tempIr;

#define emit(...) ({ \      
  if (isTempIr) { \                       //如果等於一時，會進這邊
    sprintf(tempIrp, __VA_ARGS__); \      //不會印出來，而且我們將其在此存起來
    tempIrp += strlen(tempIrp);\
  } else { \                              //如果等於零時，會進這邊
    printf(__VA_ARGS__);\                 //在這邊我們就會印出來
  }\
})
```
>* 這邊是FOR()所做的改變
```
void FOR() { //(assign e;e)stmt
  int forBegin = nextLabel();
  int forEnd = nextLabel();
  emit("(L%d)\n",forBegin);
  skip("for");
  skip("(");
  ASSIGN(); //e.g:i = 0;
  int e2 = E(); //e.g:i < 10;
  emit("if not t%d goto L%d\n",e2,forEnd);
  skip(";");
  isTempIr = 1;                //先給isTempIr = 1;
  int e3 = E();                //這邊只會存起來，並不會印出來
  isTempIr = 0;                //這邊isTempIr = 0;下一次呼叫函數時就會印出來剛剛儲存的
  char e3str[10000];
  strcpy(e3str, tempIr);       //將tempIr複製，並給e3str，並回傳e3str
  skip(")");
  STMT();
  emit("%s\n", e3str);         //這邊將e3stru印出來(i = i + 1)
  emit("goto L%d\n",forBegin);
  emit("(L%d)\n",forEnd);
}
```