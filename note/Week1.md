## 編譯器
* C(gcc):
1. gcc -c -c fib.c -o fib :只編譯不連結
2. gcc -S fib.c -o fib.s :編譯成組合語言
3. gcc -c sum.s -o sum.o :轉成目的檔(只編譯不連結) ==>很多 .o檔可以壓成一個函式庫
* C++(g++)
1. g++ -S hello.cpp -o hello.s: c++編譯成組合語言的指令

## 建立切換分支
* git branch : 知道有哪些main在branch中
* git checkout -b master :建立一個新的master在branch中
* git branch :就可以看見產生一個新的master(並換到master中)在branch中
* git push origin master:就可以push剛剛建立的master
* git branch main: 建立分支到branch中
* git checkout main: 切換分支(Switched to branch 'main')

## 系統程式和系統軟體的差別
* 系統程式是給程式設計師所使用的語言
* 系統程式是寫成系統軟體的方式(e.g編譯器)

* 補充:
1. 編譯式(c,c++...):要先編譯程執行檔
2. 解譯式(python...):不用先編譯，直接執行，大多是沒有宣告型態的語言

