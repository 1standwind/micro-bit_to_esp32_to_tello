#include <WiFi.h>
#include <WiFiUdp.h>

static WiFiUDP udp;

//設定
static char ssid[] = "";
static char password[] = "";
static char *ip = "192.168.10.1";
static int port = 8889;

//グローバル変数定義
char get_data[255];
char packetBuffer[255];
bool wite_flg = false;
bool wifi_flg = false;

// 初期設定 
void setup() {
  // シリアルポート
  Serial.begin(115200);
  while(!Serial);
  Serial2.begin(115200,SERIAL_8N1,16,17);
  while(!Serial2);
}

// main loop
void loop() {
  int i = 0;
  get_data[0] = '\0';
  // シリアルからの書き込み待ち
  while(Serial2.available() && wite_flg == false){
    //シリアルデータ読み込み
    get_data[i] = Serial2.read();
    i++;
    wite_flg = true;
  }

  while(Serial.available() && wite_flg == false){
    //シリアルデータ読み込み
    get_data[i] = Serial2.read();
    i++;
    wite_flg = true;
  }

  // telloにデータ送信
  if(wite_flg){
    wite_flg = false;
    String message = get_data;
    Serial.println(message);
    message.trim();

    if(message == "command"){
      wifi_flg = telloConnect(ssid, password);
    } else if( wifi_flg == true ){
      int len = message.length()+1;
      char msg_char[len];
      message.toCharArray(msg_char, len);
      sendMessage(msg_char);
      delay(500);
      Serial.println(listenMessage());
    }
  }
}

// telloと接続するための関数
bool telloConnect(char* setSSID, char* setPassword){
  WiFi.begin(setSSID, setPassword);
  int i = 0;
  while ( WiFi.status() != WL_CONNECTED) {
    i++;
    if ( i > 5 ) return false;
    delay(500);
  }
  Serial.println("wifi ok");
  udp.begin(port);

  sendMessage("command");
  Serial.println(":command");
  delay(500);
  String res = listenMessage();
  Serial.println(res);
  Serial2.println(res);
  return true;
}

// telloへメッセージ送信
bool sendMessage(char* ReplyBuffer) {
  udp.beginPacket(ip, port);
  udp.printf(ReplyBuffer);
  udp.endPacket();
  return true;
}

// telloからメッセージ読み込み
String listenMessage() {
  packetBuffer[0] = '\0';
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(udp.remotePort());

    // 読んだメッセージをバッファに書き込み
    int len = udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = '\0';
    Serial.println("Contents:");
    Serial.println(packetBuffer);
  }
  // バッファ内のメッセージを返却
  return (char*) packetBuffer;
}


