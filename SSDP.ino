void SSDP_init(void) {
  String chipID = String( ESP.getChipId() ) + "-" + String( ESP.getFlashChipId() );
  // SSDP дескриптор
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
    //Если версия  2.0.0 закоментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName("ESPFORTH");
  SSDP.setSerialNumber(chipID);
  SSDP.setURL("/");
  SSDP.setModelName("tech");
  SSDP.setModelNumber(chipID + "/" + "ESPFORTH");
  SSDP.setModelURL("http://esp8266-arduinoide.ru/step12-graf-dht/");
  SSDP.setManufacturer("Tretyakov Sergey");
  SSDP.setManufacturerURL("http://www.esp8266-arduinoide.ru");
  SSDP.begin();
}
