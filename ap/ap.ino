#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <cstring>
#include <random>

// Function to generate a random MAC address
void randomMACAddress(byte *mac) {
  for (int i = 0; i < 6; ++i) {
    mac[i] = random(256);
  }
  mac[0] &= 0xFE;  // Clear multicast bit
  mac[0] |= 0x02;  // Set local bit to indicate a locally administered address
}

// Function to generate a random alphanumeric string of length 'len'
String randomString(size_t len) {
  const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  String s = "";
  for (size_t i = 0; i < len; ++i) {
    s += alphanum[random(62)];
  }
  return s;
}

void setup() {
  Serial.begin(115200);

  // Initialize random number generator with a more varied seed
  randomSeed(micros());

  // Set WiFi to AP mode
  WiFi.mode(WIFI_AP);

  // Disconnect and turn off AP
  WiFi.softAPdisconnect(true);
  delay(1000); // Wait for a bit to ensure settings are cleared
}

void loop() {
  // Randomize ESSID and password
  String xyz = randomString(3);
  String essid = "pwnfood" + xyz;
  String password = xyz + "nomnomnom";

  // Randomize and set a new MAC address
  byte mac[6];
  randomMACAddress(mac);
  wifi_set_macaddr(SOFTAP_IF, &mac[0]);

  // Configure and start the WiFi access point
  WiFi.softAP(essid.c_str(), password.c_str());

  Serial.print("SSID: ");
  Serial.print(essid);
  Serial.print(" | Password: ");
  Serial.println(password);
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Wait a bit and then check for connected clients
  delay(20000); // Wait 20 seconds to allow clients to connect
  checkConnectedClients();

  // Wait for 1 minutes before changing again
  delay(60000);
}

void checkConnectedClients() {
  if (WiFi.softAPgetStationNum() > 0) {
    Serial.println("Client(s) connected:");
    struct station_info *station = wifi_softap_get_station_info();
    while (station) {
      Serial.print("BSSID: ");
      Serial.println(macToString(station->bssid));
      station = STAILQ_NEXT(station, next);
    }
    wifi_softap_free_station_info(); // Free the memory
  } else {
    Serial.println("No clients connected");
  }
}

String macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}
