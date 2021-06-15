/*** includes ***/

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h> 
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

/*** defines ***/

#define KILO_VERSION "0.0.1"
#define KILO_TAB_STOP 8

#define CTRL_KEY(k) ((k) & 0x1f)

enum editprKey {  //在列舉中第一個設為1000，其他會依序設成1001,1002,1003
  ARROW_LEFT  = 1000,
  ARROW_RIGHT ,
  ARROW_UP ,
  ARROW_DOWN ,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

/*** data ***/

//typedef允許我們將類型稱為erow而不是struct erow
typedef struct erow {  //存除役行指向動態分配的長度與指針
  int size;
  int rsize;
  char *chars;
  char *render;
}erow;

struct editorConfig {  //用來存取終端的寬度與高度
  int cx, cy;  //初始化cx和cy用來來追蹤cursor的位置
  int rx;
  int rowoff;  //跟蹤用戶當前滾動到文件的幾行
  int coloff; //列(水平)位移變量
  int screenrows;
  int screencols;
  int numrows;
  erow *row;  //為了儲存多行，因此將row設為一個指針
  char *filename;
  char statusmsg[80];  //用來儲存現階段的訊息
  time_t statusmsg_time;   //增加時間戳，可以在幾秒鐘後將訊息刪除
  struct termios orig_termios;
};

struct editorConfig E; //全域變數E，使用E.orig_termios來替換所有的orig_termios

/*** terminal ***/

void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);

  struct termios raw = E.orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) { //沒有讀到，且錯誤不是沒有資料
    if (nread == -1 && errno != EAGAIN) die("read");
  }

  if (c == '\x1b'){
    char seq[3];

    if(read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if(read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

    if(seq[0] == '['){
      if(seq[1] >= '0' && seq[1] <= '9'){
        if(read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
        if(seq[2] == '~'){
          switch(seq[1]){
            case '1' : return HOME_KEY;
            case '3' : return DEL_KEY;
            case '4' : return END_KEY;
            case '5' : return PAGE_UP;
            case '6' : return PAGE_DOWN;
            case '7' : return HOME_KEY;
            case '8' : return END_KEY;
          }
        }
      }else{
        switch(seq[1]){
          case 'A' : return ARROW_UP;
          case 'B' : return ARROW_DOWN;
          case 'C' : return ARROW_RIGHT;
          case 'D' : return ARROW_LEFT;
          case 'H' : return HOME_KEY;
          case 'F' : return END_KEY;
        }
      }
    }else if (seq[0] == '0'){
      switch(seq[1]){
        case 'H' : return HOME_KEY;
        case 'F' : return END_KEY;
      }
    }

    return '\x1b';
  }else{
    return c;
  }
}

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

/*** row operations ***/

int editorRowCxToRx(erow *row, int cx){
  int rx = 0;
  int j;
  for(j = 0; j<cx; j++){
    if(row->chars[j] == '\t')
      rx += (KILO_TAB_STOP - 1 ) - (rx % KILO_TAB_STOP);
    rx++;
  }
  return rx;
}

void editorUpdateRow(erow *row){
  int tabs = 0;
  int j;
  for (j = 0;j < row->size; j++)
    if (row->chars[j] == '\t')  tabs++;

  free(row->render);
  row->render = malloc(row->size  + tabs*(KILO_TAB_STOP - 1) + 1);

  
  int idx = 0;
  for(j = 0; j < row->size;j++){
    if(row->chars[j] == '\t'){
      row->render[idx++] = ' ';
      while(idx % KILO_TAB_STOP != 0) row->render[idx++] = ' ';
    }else{
      row->render[idx++] = row->chars[j];
    }
  }
  row->render[idx] = '\0';
  row->rsize = idx;
}

//將原本的editorOpen()中拉出來editorAppendRow()
// editorAppendRow()為新的erow分配空間
void editorAppendRow(char *s, size_t len){
  E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1)); //我們必須跟realloc()說要分配多少字節數(sizeof(erow))，乘上我們想要的行數

  int at = E.numrows;
  E.row[at].size = len;
  E.row[at].chars = malloc(len + 1); //mallco分配一個記憶體位置
  memcpy(E.row[at].chars, s, len);  //memcpy拷貝linelen個字元從line中存到E.row.chars中
  E.row[at].chars[len] = '\0'; //將最後結束點設為'\0'
  
  E.row[at].rsize = 0;
  E.row[at].render = NULL;
  editorUpdateRow(&E.row[at]);

  E.numrows ++;
}

void editorRowInsertChar(erow *row, int at, int c){
  if(at < 0 || at > row->size) at = row->size;
  row->chars = reallco(row->chars, row->size + 2); //+2是因為我們要為空字元騰出空間 
  memmove(&row->chars[at + 1], &row->chars[at], row->size - at + 1);  //用memmove為新字符騰出空間
  row->size++;
  row->chars[at] = c;
  editorUpdateRow(row);  //使用新航的內容更新和rsize字段
}

/***editor operations***/

void editorInsertChar(int c){
  if(E.cy == E.numrows){  //如果光標位於文件末尾後的
    editorAppendRow("", 0); //添加新欄位
  }
  editorRowInsertChar(&E.row[E.cy], E.cx, c);
  E.cx++;
}

/***file i/o ***/

void editorOpen(char *filename){
  free(E.filename);
  E.filename = strdup(filename);
  
  FILE *fp = fopen(filename, "r");
  if(!fp) die("fopen");

  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while((linelen = getline(&line, &linecap, fp)) != -1){  //這行是讀多行的關鍵，當他讀完這個檔案，getline()會回傳-1
    while(linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
          
          linelen--;
        editorAppendRow(line, linelen);
  }
  free(line);
  fclose(fp);
}

/*** append buffer ***/

struct abuf {
  char *b;
  int len;
};

#define ABUF_INIT {NULL, 0}

void abAppend(struct abuf *ab, const char *s, int len) {
  char *new = realloc(ab->b, ab->len + len);

  if(new == NULL) return;
  memcpy(&new[ab->len], s, len);
  ab->b = new;
  ab->len += len;
}

void abFree(struct abuf *ab) {
  free(ab->b);
}
/*** output ***/

void editorScroll(){ //E.rowoff試紙屏幕頂部的內容
  E.rx = 0;
  if(E.cy < E.numrows) {
    E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
  }

  if(E.cy < E.rowoff){//檢查光標是否在可見窗口上，如果是則向上滾動到光標所在位置上
    E.rowoff = E.cy;
  }
  if(E.cy >= E.rowoff + E.screenrows){ //是否越過可見窗口底部
    E.rowoff = E.cy - E.screenrows + 1;
  }

  if(E.rx < E.coloff){
    E.coloff = E.rx;
  }
  if(E.rx >= E.coloff + E.screencols){
    E.coloff = E.rx - E.screencols + 1;
  }
}

void editorDrawRows(struct abuf *ab) {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    int filerow = y + E.rowoff;  //用來顯示文件的正確行範圍
    if(filerow >= E.numrows){
      if(E.numrows == 0 && y == E.screenrows / 3){ //在螢幕大小1/3的地方印
        char welcome[80];
        int welcomelen = snprintf(welcome, sizeof(welcome), "Kilo editor -- version %s", KILO_VERSION);
        if(welcomelen > E.screencols) welcomelen = E.screencols;
        int padding = (E.screencols - welcomelen) / 2;
        if (padding) {
          abAppend(ab, "~", 1);
          padding--;
        }
        while (padding--) abAppend(ab, " ", 1);
        abAppend(ab, welcome, welcomelen);
      }else{
        abAppend(ab, "~", 1);
      }
    }else{
      int len = E.row[filerow].rsize - E.coloff;
      if(len < 0) len = 0;
      if(len > E.screencols) len = E.screencols;// E.coloff做為顯示每一行字符的索引，並從行的長度中減去篇一輛左側的字符數
      abAppend(ab, &E.row[filerow].render[E.coloff], len);   
    }
    

    abAppend(ab, "\x1b[K", 3);
      abAppend(ab, "\r\n", 2);
    }  
}


void editorDrawStatusBar(struct abuf *ab) {
  abAppend(ab, "\x1b[7m", 4);
  char status[80], rstatus[80];
  int len = snprintf(status, sizeof(status), "%.20s - %d lines",
    E.filename ? E.filename : "[No Name]", E.numrows);
  int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d",
    E.cy + 1, E.numrows);
  if (len > E.screencols) len = E.screencols;
  abAppend(ab, status, len);
  while (len < E.screencols) {
    if (E.screencols - len == rlen) {
      abAppend(ab, rstatus, rlen);
      break;
    } else {
      abAppend(ab, " ", 1);
      len++;
    }
  }
  abAppend(ab, "\x1b[m", 3);
  abAppend(ab, "\r\n", 2);
}

void editorDrawMessageBar(struct abuf *ab){ //繪製新的訊息訊息欄
  abAppend(ab, "\x1b[K", 3);
  int msglen = strlen(E.statusmsg);
  if(msglen > E.screencols) msglen = E.screencols;
  if(msglen && time(NULL) - E.statusmsg_time < 5)
    abAppend(ab, E.statusmsg, msglen);
}

void editorRefreshScreen() {
  editorScroll(); //在刷新平目前調用此

  struct abuf ab = ABUF_INIT;

  abAppend(&ab, "\x1b[?25l", 6);
  //abAppend(&ab, "\x1b[2J", 4);
  abAppend(&ab, "\x1b[H", 3);

  editorDrawRows(&ab);
  editorDrawStatusBar(&ab);
  editorDrawMessageBar(&ab);

  char buf[32];
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.cy - E.rowoff) + 1,(E.rx - E.coloff) + 1);
  abAppend(&ab, buf, strlen(buf));

  //abAppend(&ab, "\x1b[H", 3);
  abAppend(&ab, "\x1b[?25h", 6);

  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}

void editorSetStatusMessage(const char *fmt, ...){
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap); //vsnprintf幫助我們製作自己的printf()風格函數，並將結果字符串儲存至E.statusmsg 中
  va_end(ap);
  E.statusmsg_time = time(NULL); //將 E.statusmsg_time 設置為當前時間，可以通過將 NULL 傳遞給 time() 來獲取
}

/*** input ***/

void editorMoveCursor(int key){  //運用上下左右鍵讓光標移動
  erow *row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
  switch(key) {
    case ARROW_LEFT:
        if(E.cx != 0){
          E.cx--;
        } else if(E.cy > 0){
          E.cy--;
          E.cx = E.row[E.cy].size;
        }
      break;
    case ARROW_RIGHT:
      if(row && E.cx < row->size){
        E.cx++;
      }else if(row && E.cx == row->size){
        E.cy++;
        E.cx = 0;
      }
      break;
    case ARROW_UP:
      if(E.cy != 0){
        E.cy--;
      }
      break;
    case ARROW_DOWN:
      if(E.cy < E.numrows){ //讓光標越過屏幕底部(但不能超過文件底部)
        E.cy++;
      }
      break;
  }

  row = (E.cy >= E.numrows)?NULL :&E.row[E.cy];
  int rowlen = row ? row->size : 0;
  if(E.cx > rowlen) {
    E.cx = rowlen;
  }
}

void editorProcessKeypress() {
  int c = editorReadKey();

  switch (c) {
    case CTRL_KEY('w'):
      write(STDOUT_FILENO, "\x1b[2J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      exit(0);
      break;

    case HOME_KEY:
      E.cx = 0;
      break;

    case END_KEY:
      if(E.cy < E.numrows)
        E.cx = E.row[E.cy].size;
      break;

    case PAGE_UP:
    case PAGE_DOWN:
      {
        // 讓 Page Up 和 Page Down 鍵向上或向下滾動整個頁面。
        if(c == PAGE_UP){
          E.cy = E.rowoff;
        }else if(c == PAGE_DOWN){
          E.cy = E.rowoff + E.screenrows - 1;
          if(E.cy > E.numrows) E.cy = E.numrows;
        }

        int times = E.screenrows;
        while (times--)
          editorMoveCursor(c == PAGE_UP ? ARROW_UP :ARROW_DOWN);         
      }
      break;

    case ARROW_UP:
    case ARROW_DOWN:
    case ARROW_LEFT:
    case ARROW_RIGHT:
      editorMoveCursor(c);
      break;

    default:
      editorInsertChar(c);
      break;
  }
}

/*** init ***/

void initEditor() { //設置initEditor()來初始化E結構中的所有字段
  
  //設定cursor一開始的位置在(0,0)的位置
  E.cx = 0; 
  E.cy = 0;
  E.rx = 0;
  E.rowoff = 0; //初始化為0，默認滾動到文件頂部
  E.coloff = 0;
  E.numrows = 0;
  E.row = NULL;
  E.filename = NULL;
  E.statusmsg[0] = '\0';  //初始化為空字串，因此默認情控下不會顯示任何消息
  E.statusmsg_time = 0;   //包含我們設置消息狀態時的時間戳

  if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
  E.screenrows -= 2 ;
}

int main(int argc, char *argv[]) {
  enableRawMode();
  initEditor();
  if(argc >= 2){
    editorOpen(argv[1]);
  }

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
}
