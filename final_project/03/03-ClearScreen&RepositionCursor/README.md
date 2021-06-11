# 清除螢幕&定位移動光標

* `write(STDOUT_FILENO, "\x1b[2J", 4);`清除螢幕和迴滚緩衝區

* `write(STDOUT_FILENO, "\x1b[H", 3);` :定位移動光標的意思
---
**參考資料:**

* [kilo](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)

