  // Sender (tx)
  // A. Inácio Morais
  // 06/2024

#include <esp_now.h>
#include <WiFi.h>

  // pin 22 - GPIO2
#define PUSH_BUTTON_PIN_1 2
  // pin 18 - GPIO12
#define PUSH_BUTTON_PIN_2 12
  // pin 17 - GPIO14
#define PUSH_BUTTON_PIN_3 14
  // pin 21 - GPIO15
#define PUSH_BUTTON_PIN_4 15

  // ctrl vars
bool pb1_status = 0;
bool pb2_status = 0;
bool pb3_status = 0;
bool pb4_status = 0;
bool sendit = 0;

  // REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x94, 0xB5, 0x55, 0x26, 0x44, 0x58};

  // Structure to send data matching the receiver structure
typedef struct struct_message {
  bool a;
  bool b;
  bool c;
  bool d;
} struct_message;

  // Create a struct_message called myData
struct_message myData;

  // ESPNOW peer information parameters
esp_now_peer_info_t peerInfo;

  // Status of sending ESPNOW data
//void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//}

void setup() {
    // initialize the pushbutton pins as input with pulldown
  pinMode(PUSH_BUTTON_PIN_1, INPUT_PULLDOWN);
  pinMode(PUSH_BUTTON_PIN_2, INPUT_PULLDOWN);
  pinMode(PUSH_BUTTON_PIN_3, INPUT_PULLDOWN);
  pinMode(PUSH_BUTTON_PIN_4, INPUT_PULLDOWN);

    // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

    // Initialize ESPNOW function
  esp_now_init();
  
    // Register callback function of sending ESPNOW data
  //esp_now_register_send_cb(OnDataSent);

    // Register peer using memcpy
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

    // Add a peer to peer list
  esp_now_add_peer(&peerInfo);
}
 
void loop() {
    // pin 22 - GPIO2
  if (digitalRead(PUSH_BUTTON_PIN_1) == 1) {
    myData.a = 1;
    pb1_status = 1;
    sendit = 1;
  }

  if (digitalRead(PUSH_BUTTON_PIN_1) == 0 && pb1_status == 1) {
    myData.a = 0;
    pb1_status = 0;
    sendit = 1;
  }

    // pin 18 - GPIO12
  if (digitalRead(PUSH_BUTTON_PIN_2) == 1) {
    myData.b = 1;
    pb2_status = 1;
    sendit = 1;
  }

  if (digitalRead(PUSH_BUTTON_PIN_2) == 0 && pb2_status == 1) {
    myData.b = 0;
    pb2_status = 0;
    sendit = 1;
  }

    // pin 17 - GPIO14
  if (digitalRead(PUSH_BUTTON_PIN_3) == 1) {
    myData.c = 1;
    pb3_status = 1;
    sendit = 1;
  }

  if (digitalRead(PUSH_BUTTON_PIN_3) == 0 && pb3_status == 1) {
    myData.c = 0;
    pb3_status = 0;
    sendit = 1;
  }

    // pin 21 - GPIO15
  if (digitalRead(PUSH_BUTTON_PIN_4) == 1) {
    myData.d = 1;
    pb4_status = 1;
    sendit = 1;
  }

  if (digitalRead(PUSH_BUTTON_PIN_4) == 0 && pb3_status == 1) {
    myData.d = 0;
    pb4_status = 0;
    sendit = 1;
  }

  if (sendit == 1) {
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    sendit = 0;
  }
}
