#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
String lastConnectedSSID = "";
String lastConnectedBSSID = "";
String lastConnectedPassword = "";

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);

  // Start WiFi scan
  scanNetworks();
}

void loop() {
  // If not connected or the network has changed, start a new scan
  if (WiFi.status() != WL_CONNECTED || WiFi.SSID() != lastConnectedSSID) {
    WiFi.disconnect(); // Disconnect from the current network
    lastConnectedSSID = "";
    lastConnectedPassword = "";
    scanNetworks(); // Scan for new networks
  }

  // Wait a bit before the next loop iteration
  delay(5000); // Reduced delay to 5 seconds for more frequent scanning
}

void scanNetworks() {
  Serial.println("Scanning for WiFi networks...");
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");

  if (n == 0) {
    Serial.println("No networks found");
  } else {
    for (int i = 0; i < n; ++i) {
      // Check if the network ESSID starts with "pwnfood"
      String ssid = WiFi.SSID(i);
      if (ssid.startsWith("pwnfood")) {
        String xyz = ssid.substring(7); // Extract the 'XYZ' part of the ESSID
        String password = xyz + "nomnomnom"; // Construct the password
        String currentBSSID = WiFi.BSSIDstr(i);

        if (currentBSSID != lastConnectedBSSID) {
          randomMACAddress();
          lastConnectedBSSID = currentBSSID;
        }

        lastConnectedSSID = ssid;
        lastConnectedPassword = password;
        connectToNetwork(ssid, password);
        break; // Stop scanning once a matching network is found
      }
    }
  }
}

void randomMACAddress() {
  byte mac[6];
  for (int i = 0; i < 6; ++i) {
    mac[i] = random(256);
  }
  mac[0] &= 0xFE;  // Clear multicast bit
  mac[0] |= 0x02;  // Set local bit to indicate a locally administered address

  wifi_set_macaddr(STATION_IF, &mac[0]);

  Serial.print("New MAC Address: ");
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n", 
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void connectToNetwork(String ssid, String password) {
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print(" with password ");
  Serial.println(password);

  WiFi.begin(ssid.c_str(), password.c_str());

  // Wait for connection
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Client BSSID (MAC Address): ");
    Serial.println(WiFi.macAddress());
  } else {
    Serial.println("\nFailed to connect.");
  }
}
