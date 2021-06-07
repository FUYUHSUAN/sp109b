```makefile
kilo: kilo.c
	$(CC) kilo.c -o kilo -Wall -Wextra -pedantic -std=c99

```
* 只有linux上能使用cc
* kilo是我們想要建立的，kilo.c是我們想要編譯的
* `$(CC)` :gcc的意思
* `-Wall` :打出所有警告訊息，例如在初始化之前使用變量。
* `-Wextra` `-pedantic` :給出更多警告
* `-std=c99` :c99，這是一種標準
