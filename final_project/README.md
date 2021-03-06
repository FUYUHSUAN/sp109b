# 期末專案介紹
>* 主題:編輯器
>* 班級:資工二
>* 姓名:傅于軒
>* 指導老師:陳鍾誠老師
>* 來源非100%原創，參考[kilo](https://viewsourcecode.org/snaptoken/kilo/index.html)來學習製作，在[06](https://github.com/FUYUHSUAN/sp109b/tree/main/final_project/06-Try_by_myself/01)是學期kilo功能自行做出來的

## 目錄

* 前言
* 期末作業的介紹
* 編輯器的簡介

## 前言

* 首先要感謝鍾誠老師的教導，有問題時能一步一步協助解惑，並且提供許多資料，讓我學習，這堂系統程式的課及作業，讓我精進了許多能力。

* 接者，我的專案是學習並理解和增加一些編譯器的小功能，此專案我參考了[kilo](https://viewsourcecode.org/snaptoken/kilo/index.html)這個製作編輯器的教材。

* 心得:我看完kilo這個編輯器到Chapter5之後，我雖然不是到能完全理解整段程式碼，但是一步一步從0開始做，卻讓我學習到許多東西， 有些是新的c語言與法，有些是新的編輯器概念。

## 期末作業的介紹

* 我的期末作業，是一步一步學習kilo，所以我學習到的東西，和那段主要的程式碼，我都寫在我的每一個小結中的README.md中，有些是我上網尋找到學習的c的新語法的筆記，有些是kilo中每次增加的函數之用途。

* 作業位置: [final_project](https://github.com/FUYUHSUAN/sp109b/tree/main/final_project) 我一步一步從01->05都是學習[kilo](https://viewsourcecode.org/snaptoken/kilo/index.html)，06是我做的小的新功能

* 指令介紹
>* `make`   :來做編譯
>* `rm -rf kilo.c`   :如果存在kilo.c時，就先用這個指令來刪除，因為我的Makefile沒有做clean
>* `./kilo` :可以用來創建一個新文件，並在裡面將其編譯
>* `./kilo kilo.c` :用來執行kilo這個程式

* 功能介紹(./kilo kilo.c進去後的指令)
>* `Ctrl+W` :用來離開。我改成+W因為，在VScode中執行他為抓取這個快捷鍵
>* `Ctrl+S` :用來存檔
>* `Ctrl+R` :用來跳到指定的行數，下面會顯示有多少行
>* `Page Up` :用來翻到前一頁
>* `Page Down` :用來翻到下一頁
>* 

* 使用方法
>* 執行`./kilo kilo.c`如果編輯後不儲存，直接跳出，需要按三次`Ctrl+W`
>* 執行`./kilo kilo.c`如果編輯儲存，按`Ctrl+S`，儲存完後按下`Ctrl+W`後離開
>* 執行`./kilo`產生空白檔案，如果要儲存，按下`Ctrl+S`並輸入檔案名稱，接者按下`Enter`，就儲存完了，接者按下`Ctrl+W`就可離開程式，然後我們就可以看見剛剛編輯並創建的檔案

## 編輯器的簡介
* 編輯器的世界我們要掌握所有鍵盤的按鍵，我們才能準確準確的製作出編輯器，因此我們會在程式02中做出能控制出所有鍵盤的部分

* 接者要做出輸出和輸入的功能，因此在03中實現

* 先下來要做能看見整個檔案的部分，並且讀取檔案的部分，這時現於04中

* 接下來就是能夠編輯文件，位於05的部分，到這裡編輯器的基本功能就完成了



