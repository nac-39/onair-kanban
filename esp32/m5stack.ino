#include <HTTPClient.h>
#include <M5Stack.h>

// Wi-FiのSSID
char *ssid = "******";
// Wi-Fiのパスワード
char *password = "******";

void setup() {
  M5.begin(true, false, true);

  // スタート
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  Serial.print("START");  // Arduino のシリアルモニタにメッセージを出す
  M5.Lcd.print(
      "START");  // M5Stack LCDディスプレイにメッセージを出す（英語のみ）

  // WiFi 接続開始
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    // Arduino のシリアルモニタ・M5Stack LCDディスプレイ両方にメッセージを出す
    Serial.print(".");
    M5.Lcd.print(".");
  }

  M5.Lcd.setCursor(10, 40);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  Serial.println(
      "");  // Arduino のシリアルモニタにメッセージを出し改行が最後に入る
  M5.Lcd.println(
      "");  // M5Stack
            // LCDディスプレイにメッセージを出す改行が最後に入る（英語のみ）

  Serial.println(
      "WiFi Connected.");  // Arduino のシリアルモニタにメッセージを出す
  M5.Lcd.println(
      "WiFi Connected.");  // M5Stack
                           // LCDディスプレイにメッセージを出す（英語のみ）
  M5.Lcd.setTextSize(6);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(10, 100);
}

String get_status() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);

  HTTPClient httpClient;

  // URL 設定
  String url = "https://********.workers.dev/status";

  httpClient.begin(url);
  String response = "";
  // ポストする
  int status_code = httpClient.GET();
  if (status_code == 200) {
    response = httpClient.getString();

    Serial.println("sended.");
  }
  httpClient.end();
  return response;
}

void loop() {
  M5.update();

  String res = get_status();

  if (res == "in_meeting") {
    M5.Lcd.fillScreen(MAROON);
    M5.Lcd.println("ON AIR");
  } else if (res == "in_mute") {
    M5.Lcd.fillScreen(NAVY);
    M5.Lcd.println("MUTE");
  }
  delay(3000);
}
