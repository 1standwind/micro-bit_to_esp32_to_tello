# micro-bit_to_esp32_to_tello
## 概要
micro:bit と Tello を ESP32 を中継して通信するためのESP32 by Arduino IDE用コード

micro:bit用 makecodeサンプル 

[Arduino IDE 開発環境構築参考資料](https://qiita.com/asagi_toyo/items/f5d07a6ed4d6667617f7) 

[makecode](https://makecode.microbit.org/#) 

## 回路図
![名称未設定ファイル](https://github.com/user-attachments/assets/36009ace-7375-4943-a388-04195d2a0077) 

## 設定
esp32_2_tello.ino 6〜10行目 

```
//設定
static char ssid[] = "";
static char password[] = "";
static char *ip = "192.168.10.1";
static int port = 8889;
```
