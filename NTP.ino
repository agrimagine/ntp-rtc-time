// Copyright 2018 © Valentin DEVILLE <contact@valentin-deville.eu>
// For Agrimagine

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <NTPClient.h>

#include <Wire.h>
#include <DS3231.h>

// Enter a MAC address for your controller below (or fake)
byte mac[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07
};

DS3231 clock;
RTCDateTime dt;
EthernetClient client;
EthernetUDP ntpUDP;
// You can specify the time server pool and the offset (in seconds, can be changed later with setTimeOffset() ).
// Additionaly you can specify the update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "fr.pool.ntp.org");

void setup() {
  Serial.begin(115200);

  Serial.println("");
  Serial.println("");
  Serial.println(" .oO Welcome to the RTC NTP update for Agrimagine Oo.");
  Serial.println("");
  Serial.println("");

  if (Ethernet.begin(mac) == 0) {
    for (;;) {
      Serial.println("Failed to configure Ethernet using DHCP");
      delay(1000);
    }
  } else {
    Serial.print("IP address: ");
    Serial.println(Ethernet.localIP());
    Serial.println("");
    Serial.println("");

    clock.begin();

    timeClient.begin();
  }
}


int number = 0;

void loop() {
  timeClient.update();

  Serial.print("NTP: Unix timestamp: ");
  Serial.print(timeClient.getEpochTime());
  Serial.print(" (");
  Serial.print(timeClient.getFormattedTime());
  Serial.println(")");

  dt = clock.getDateTime();

  Serial.print("RTC time: ");
  Serial.print(clock.dateFormat("U", dt));
  Serial.print(" (");
  Serial.print(clock.dateFormat("d F Y H:i:s",  dt));;
  Serial.println(")");

  Serial.println("");
  Serial.println("");
  Serial.println("");

  if (number == 3) {
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("      >>> RTC was updated ! <<<");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    clock.setDateTime(timeClient.getEpochTime());
  }

  number++;
  delay(3000);
}
