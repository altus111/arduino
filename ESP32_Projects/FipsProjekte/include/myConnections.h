

void Wifi_Connect(){
  const char* ssid = "UPC0128016";             // Network name.
  const char* password = "c9zxScwDnndq";            // Password network.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
   Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}