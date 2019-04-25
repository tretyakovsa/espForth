void handleForth() {
  // проверяем строку command на не пустое
  static boolean wordsOk;
  //boolean wordsOk;
  //if (command != "" && command != " ") { // если команд нет
  if (command != "") { // если команд нет
    command.trim();
    command += " ";
    Serial.print("command =");
    Serial.print(command);
    Serial.println("|");
    // Получаем первое слово
    String teg = selectToMarker (command, " ");
    if (teg == ":") { // если попытка определить новое слово
      dic = selectToMarker (command, " ;") + " ;\r\n" + dic; // Поместить в словарь все определение
      writeFile("vocabulary.txt", dic );
      command = deleteBeforeDelimiter(command, ";"); // Удалить из command отработанные символы
      teg = ""; // сбросить тег чтоб больше не проверялось
      //Serial.print("dic =");
      //Serial.print(dic);
      //Serial.println("|");
      wordsOk = 1;
    }
    // Если получено число
    int tegN = teg.toInt();
    if (teg == (String)tegN) {
      commandDel();
      push(tegN);
      wordsOk = 1;
      Serial.println("num");
    } else { // Иначе это слово
      Serial.println("word");

      if (!wordsOk) wordsOk = vocabulary(teg);

      if (teg == "+") {
        commandDel();
        push(pop() + pop());
        wordsOk = 1;
      }
      if (teg == "-") {
        commandDel();
        swap();
        push(pop() - pop());
        wordsOk = 1;
      }
      if (teg == "SWAP") {
        commandDel();
        swap();
        wordsOk = 1;
      }
      if (teg == "*") {
        commandDel();
        push(pop() * pop());
        wordsOk = 1;
      }
      if (teg == "/") {
        commandDel();
        swap();
        push(pop() / pop());
        wordsOk = 1;
      }
      if (teg == "WORDS") {
        commandDel();
        words();
        wordsOk = 1;
      }
      if (teg == "EMIT") {
        commandDel();
        sendWS((String)char(pop()));
        wordsOk = 1;
      }

      if (teg == "") {
        command = "";
        wordsOk = 1;
      }
      //if (!wordsOk) wordsOk = vocabulary(teg);


      Serial.print("wordsOk = ");
      Serial.print(wordsOk);
      Serial.println("|");
      if (wordsOk == 0) {
        //commandDel();
        sendWS(teg + "?");
        sendWS("\r\n");
        command = "";
      }
    }

    if (command == "") {
      String stackN = stackPrint();
      sendWS(stackN);
      //wordsOk = 0;
    }
  }
  wordsOk = 0;
}

void swap() {
  int top = pop();
  int top1 = pop();
  push(top);
  push(top1);
}

void commandDel() {
  command = deleteBeforeDelimiter(command, " ");
}

boolean vocabulary(String teg) {
  int start = dic.indexOf(": " + teg);
  if (start != -1) {
    String temp = dic.substring(start);
    temp = selectToMarker (temp, ";\r\n");
    temp.replace(": " + teg + " ", "");
    //temp.replace(";","");
    commandDel();
    command = temp + command;

    Serial.print("temp =");
    Serial.print(temp);
    Serial.println("|");
    return 1;
  } else return 0;
}
