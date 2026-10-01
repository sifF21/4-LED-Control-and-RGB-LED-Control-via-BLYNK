/***************************************
 * KONTROL LAMPU VIA BLYNK (NEW BLYNK 2)
 * Board   : ESP32 DEVKIT
 * Input   : NEW Blynk
 * Output  : LED & LED RGB
 * ESP32 Starter IoT Ardutech 
 * www.ardutech.com
 ****************************************/

#define BLYNK_TEMPLATE_ID "TMPL6bU9DCRzs"
#define BLYNK_TEMPLATE_NAME "LED Control"
#define BLYNK_AUTH_TOKEN "GIZk9T8j53G-FGq9WcqM2hwkc4VxFzLU"
#define BLYNK_PRINT Serial  

#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Definisi Pin Sesuai Skematik
#define LED1_PIN 23
#define LED2_PIN 22
#define LED3_PIN 19
#define LED4_PIN 18

#define RGB_RED_PIN   32
#define RGB_BLUE_PIN  33
#define RGB_GREEN_PIN 25

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Protos";
char pass[] = "PowerOverWhelming";

LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;
boolean st;

//======== Kontrol LED Tunggal ========
BLYNK_WRITE(V1)
{ 
  int value1 = param.asInt();
  digitalWrite(LED1_PIN, value1);   
}

BLYNK_WRITE(V2)
{ 
  int value2 = param.asInt();
  digitalWrite(LED2_PIN, value2);   
}

BLYNK_WRITE(V3)
{ 
  int value3 = param.asInt();
  digitalWrite(LED3_PIN, value3);   
}

BLYNK_WRITE(V4)
{ 
  int value4 = param.asInt();
  digitalWrite(LED4_PIN, value4);   
}

//======== Kontrol LED RGB ========
BLYNK_WRITE(V5) // Slider Blue
{
  int sliderValue = param.asInt();
  analogWrite(RGB_BLUE_PIN, sliderValue);
}

BLYNK_WRITE(V6) // Slider Red
{
  int sliderValue = param.asInt();
  analogWrite(RGB_RED_PIN, sliderValue);
}

BLYNK_WRITE(V7) // Slider Green
{
  int sliderValue = param.asInt();
  analogWrite(RGB_GREEN_PIN, sliderValue);
}

//==============================================
void cek_koneksi(){ 
  st = Blynk.connected();
  if(st == true){
    lcd.setCursor(0, 1);     
    lcd.print("Koneksi Sukses");
  }
  else{ 
    lcd.setCursor(0, 1);     
    lcd.print("Koneksi Gagal ");
  }
}

//=============================
void setup()
{
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT); 

  pinMode(RGB_RED_PIN, OUTPUT); 
  pinMode(RGB_BLUE_PIN, OUTPUT); 
  pinMode(RGB_GREEN_PIN, OUTPUT); 

  lcd.init();  
  lcd.backlight(); 
  lcd.setCursor(0, 0); 
  lcd.print(" ESP32 Kontrol ");
  lcd.setCursor(0, 1);    
  lcd.print("Lampu via Blynk");
  delay(2000); 
  lcd.clear();    
  lcd.print("Tunggu Koneksi.."); 

  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  cek_koneksi(); 
}

//=============================
void loop()
{
  Blynk.run();  
}
