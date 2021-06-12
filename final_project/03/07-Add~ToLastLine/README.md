# 了解Window 大小，較難方法

這邊整段做完可以準確的知道windows的大小(測試過，無論方大縮小他都能抓到)，然後按下Ctrl+w就能退出

* 程式碼大部分解釋都註解在程式碼中



* C命令:向右移動光標 B命令 :向下移動光標
```c 
int getWindowSize(int *rows, int *cols){
	struct winsize ws;
	
	if (1 || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0){ //測試回退分
		if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;     //C命令:向右移動光標 B命令 :向下移動光標
		return getCursorPosition(rows, cols);
		}else {
			*cols = ws.ws_col;
			*rows = ws.ws_row;
			return 0;
		}
}
```
---

* 得到鼠標位置

  ```c
  int getCursorPosition(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;

    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1; //輸出鼠標的位置

    while (i < sizeof(buf) - 1) { //讀取剛剛輸出的位置
      if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
      if (buf[i] == 'R') break;
      i++;
    } // eascape sequence = esc[num1;num2R 第一個數字是行，第二個則是列
    buf[i] = '\0';

    if (buf[0] != '\x1b' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

    return 0;
  }

  ```
---
* 得到windows的大小

  ```c
  int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
      if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;  //C命令:向右移動光標 B命令 :向下移動光標
      return getCursorPosition(rows, cols);
    } else {
      *cols = ws.ws_col;
      *rows = ws.ws_row;
      return 0;
    }
  }
  ```
---
**參考資料:**



* [kilo](https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html)

