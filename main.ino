// --------------------Выделяем строку до маркера --------------------------------------------------
String selectToMarker (String str, String found) {
  int p = str.indexOf(found);
  return str.substring(0, p);
}
// -------------------Выделяем строку от конца строки до маркера ---------------------
String selectToMarkerLast (String str, String found) {
  int p = str.lastIndexOf(found);
  return str.substring(p + found.length());
}
//----------------------Удаляем все до символа разделителя -----------------
String deleteBeforeDelimiter(String str, String found) {
  int p = str.indexOf(found) + found.length();
  return str.substring(p);
}
//----------------------Удаляем все до символа разделителя -----------------
String deleteBeforeDelimiterTo(String str, String found) {
  int p = str.indexOf(found);
  return str.substring(p);
}
// -------------------Удаляем строку от конца строки до маркера ---------------------
String deleteToMarkerLast (String str, String found) {
  int p = str.lastIndexOf(found);
  return str.substring(0, p);
}
//--------Выделяем строку от маркера до маркера
String selectFromMarkerToMarker(String str, String found, int number) {
  if (str.indexOf(found) == -1) return "not found"; // если строки поиск нет сразу выход
  str+=found; // добавим для корректного поиска
  uint8_t i = 0; // Индекс перебора
  do {
    if (i == number) return selectToMarker(str, found); // если индекс совпал с позицией законцим вернем резултат
    str = deleteBeforeDelimiter(str, found);  // отбросим проверенный блок до разделителя
    i++; // увеличим индекс
  } while (str.length() != 0); // повторим пока строка не пустая
  return "not found"; // Достигли пустой строки и ничего не нашли
}
// ------------- Чтение файла в строку --------------------------------------
String readFile(String fileName, size_t len ) {
  File configFile = SPIFFS.open("/" + fileName, "r");
  if (!configFile) {
    return "Failed";
  }
  size_t size = configFile.size();
  if (size > len) {
    configFile.close();
    return "Large";
  }
  String temp = configFile.readString();
  configFile.close();
  return temp;
}
// ------------- Запись строки в файл --------------------------
String writeFile(String fileName, String strings ) {
  File configFile = SPIFFS.open("/" + fileName, "w");
  if (!configFile) {
    return "Failed to open file";
  }
  configFile.print(strings);
  configFile.close();
  return "Write sucsses";
}
