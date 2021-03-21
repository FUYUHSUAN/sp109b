## for
>* for大部分程式碼都和if相同，根據老師上課所提供的改寫的
>* 程式碼放在HW\02\for裡面
* 程式碼:
FOR()
```
void FOR() { 
  int forBegin = nextLabel(); //開始的label
  int forEnd = nextLabel();   //結束的label
  emit("(L%d)\n",forBegin);
  skip("for");
  skip("(");
  ASSIGN();                  //i = 0; 在這邊沒有skip(";");是因為在ASSUGN()這個函式中已經有做了
  int e2 = E();              //i <= 10; 處理裡面的符號
  emit("if not t%d goto L%d\n",e2,forEnd);
  skip(";");
  int e3 = E();
  skip(")");
  STMT();
  emit("goto L%d\n",forBegin);
  emit("(L%d)\n",forEnd);
}
```

>* 執行/compilerc test/for.c
>* for.c
```
for(i=0;i<=5;i++){
        a=a+1;
}
```

>* 執行結果:
```
============ parse =============
(L0)
t0 = 0
i = t0
t1 = i
t2 = 5
t3 = t1 <= t2     //判斷i是否小於等於10
if not t3 goto L1 //如果i沒有小於10，則會跳出此迴圈到L1那個標記那邊
i = i + 1         //i++
t4 = i            
t5 = a
t6 = 1
t7 = t5 + t6
a = t7
goto L0
(L1)
```

* 接著還需要更改F()
>* 我的for2.c就是測試--的功能
```
int F() {
  int f;
  if (isNext("(")) { // '(' E ')'
    next(); // (
    f = E();
    next(); // )
  } else { // Number | Id
    f = nextTemp();
    char *item = next();
    if(isdigit(*item)){               //判斷是不是數字
      emit("t%d = %s\n", f, item);
    }else{
      if(isNext("++")){                //可以判斷++
        next();
        emit("%s = %s + 1\n", item, item);
      }
      if(isNext("--")){               //可以判斷--
        next();
        emit("%s = %s - 1\n", item,item);
      }
      emit("t%d = %s\n", f, item);
    }
  }
  return f;
}
```
>* for2.c
```
for(i=5;i>=0;i--){
        a=a+1;
}
```
>* for2.c執行結果
```
============ parse =============
(L0)
t0 = 5
i = t0
t1 = i
t2 = 0
t3 = t1 >= t2
if not t3 goto L1
i = i - 1
t4 = i
t5 = a
t6 = 1
t7 = t5 + t6
a = t7
goto L0
(L1)
```

