# Pwangotchi Food

My Pwnagotchi was hungry when just sitting at home or work. I needed a way to feed it when I'm stuck inside so I grabbed a couple of Wemos D1 Mini v4 from my pile and created an Wireless Access Point and Client for my little digital pet to feed on. 

## Installation

You will need 2 ESP8266 microcontrollers to use this code. You need to have the Arduino IDE installed and set up for ESP8266 development. As mentioned, I use Wemos D1 Mini v4. You can follow the instructions on the [ESP8266 Arduino Core's GitHub page](https://github.com/esp8266/Arduino) to set up your environment. If you are using the D1 Mini I would check out the [Wemos tutorial](https://www.wemos.cc/en/latest/tutorials/d1/get_started_with_arduino_d1.html#:~:text=,Tools%E2%86%92Board%3Axxx%20Choose%20your%20right%20board) first.

### Dependencies

- ESP8266WiFi
- ESP8266WiFiMulti

These libraries are included in the standard ESP8266 board package for the Arduino IDE.

## Usage

### Access Point (AP) Setup

1. Open `ap.ino` in the Arduino IDE.
2. Select your ESP8266 board type and port.
3. Upload the code to your ESP8266.

### Client Setup

1. Open `client.ino` in the Arduino IDE.
2. Select your ESP8266 board type and port.
3. Upload the code to a second ESP8266.

### Operation

- Plug them in to separate power sources.
- The AP will create a WiFi network with a partially random SSID and password, and it will change these, along with its MAC address, every 1.5 minutes (you can change this.)
- The Client will continuously scan for networks following the naming convention of the AP, connect to the AP when found, and display its connection details.
- AP will print it's ESSID, Password, and IP address. It will also print out the clients BSSID if it sees it connected.
- Client will print out the ESSID, and password its connecting to along with the IP address and BSSID it connects to the AP with.
## Future Implementation Ideas
- ### Serial Interface Commands
	- AP
		- Set SSID
		- Set Password
		- Toggle MAC randomization
		- Reset AP
		- Show status
	- Client
		- Scan Networks
		- Connect to Network
		- Disconnect from network
		- Show Status
		- Set Client MAC
		- Toggle Auto-Reconnect
	- General
		- Help
		- Reset
		- About
- ### Web interface
	- AP config
	- Client connection status
	- Wireless Signal Strength
	- Deauth detection
	- Logging
- ### Security...
