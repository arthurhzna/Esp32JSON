#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Deklarasi Variable dan Konstanta
String wifiSSID = "Python";
String wifiPassword = "1234arthur";
// const IPAddress routerIp(192, 168, 0, 1);
// String googlDotCom = "www.google.com";

// Deklarasi Fungsi
void connectWifi();
void getHttp();
void postHttp();

void setup()
{
  Serial.begin(9600);
  connectWifi();
  // getHttp();
  postHttp();
}

void loop()
{
}

void getHttp()
{
  String url = "https://reqres.in/api/users/2";
  HTTPClient http;
  String response;

  http.begin(url);
  http.GET();

  response = http.getString();
  Serial.println(response);

  StaticJsonDocument<1024> doc;
  deserializeJson(doc, response);
  JsonObject obj = doc.as<JsonObject>();

  String data = obj[String("data")];
  String support = obj[String("support")];

  Serial.println(data);
  Serial.println(support);
}

void postHttp()
{
  String url = "https://reqres.in/api/register";
  HTTPClient http;
  String response;

  StaticJsonDocument<200> buff;
  String jsonParams;
  buff["email"] = "eve.holt@reqres.in";
  buff["password"] = "pistol";

  serializeJson(buff, jsonParams);
  Serial.println(jsonParams);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  http.POST(jsonParams);
  response = http.getString();
  Serial.println(response);
}



void connectWifi()
{
  Serial.println("Connecting To Wifi");
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Wifi Connected");
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.RSSI());
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.dnsIP());

  // if (Ping.ping(googlDotCom.c_str()))
  // {
  //   Serial.println("Connected to Internet");
  // }
}
