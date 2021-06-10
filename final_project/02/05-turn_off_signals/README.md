# 關閉signals

這段程式關掉了Ctrl-C,Ctrl-Z,Ctrl-S,Ctrl-Q,Ctrl-V,Ctrl-M

* `make` : 先編譯

* `Ctrl-C,Ctrl-Z` :是由`ISIG`來控制

* `Ctrl-S,Ctrl-Q` :是由`IXON`來控制

* `Ctrl-V` :是由`IEXTEN`來控制

* `Ctrl-M` :是由`ICRNL`來控制

* 這段程式也處理了控制輸出字元的方式也就是`raw.c_oflag &= ~(OPOST);`

* `raw.c_iflag` :輸入模式 =>控制輸出字元

* `raw.c_oflag` :輸出模式 =>控制輸出字元

* `raw.c_cflag` :控制模式 =>控制串列埠的鮑率、同位元、停止位元等

* `raw.c_lflag` :局部模式 => 控制串列埠如何處理輸入字元
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

