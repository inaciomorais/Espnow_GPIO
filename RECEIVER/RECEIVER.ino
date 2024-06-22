  // Receiver (rx)
  // A. Inácio Morais
  // 06/2024

#include <esp_now.h>
#include <WiFi.h>

  // pin 22 - GPIO2
#define LED_PIN_1 2
  // pin 18 - GPIO12
#define LED_PIN_2 12
  // pin 17 - GPIO14
#define LED_PIN_3 14
  // pin 21 - GPIO15
#define LED_PIN_4 15

unsigned long lastTime = 0;  
unsigned long failSafeDelay = 10;  // 10ms Timer FailSafe

  // Structure to receive data matching the sender structure
typedef struct struct_message {
    bool a;
    bool b;
    bool c;
    bool d;
} struct_message;

  // Create a struct_message called myData
struct_message myData;

  // Callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  //Serial.print(myData.a);
  //Serial.print(myData.b);
  //Serial.print(myData.c);
  //Serial.println(myData.d);

  if (myData.a == 1) digitalWrite(LED_PIN_1, HIGH);
  else digitalWrite(LED_PIN_1, LOW);

  if (myData.b == 1) digitalWrite(LED_PIN_2, HIGH);
  else digitalWrite(LED_PIN_2, LOW);

  if (myData.c == 1) digitalWrite(LED_PIN_3, HIGH);
  else digitalWrite(LED_PIN_3, LOW);

  if (myData.d == 1) digitalWrite(LED_PIN_4, HIGH);
  else digitalWrite(LED_PIN_4, LOW);

  lastTime = millis();
}
 
void setup() {
    // initialize the led pins
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);

    // Initialize Serial Monitor
  //Serial.begin(115200);

    // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

    // Initialize ESPNOW function
  esp_now_init();

    // Callback function of receiving ESPNOW data.
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
 
void loop() {
    // Turning Outputs Off while Connection Lost
  if ((millis() - lastTime) > failSafeDelay) {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
    digitalWrite(LED_PIN_4, LOW);

    lastTime = millis();
  }
}