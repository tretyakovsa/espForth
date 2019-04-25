String stackPrint() {
  String stackSrt = String(ESP.getFreeHeap());
  stackSrt += " ";
  stackSrt += stack[stackTop - 4];
  stackSrt += " ";
  stackSrt += stack[stackTop - 3];
  stackSrt += " ";
  stackSrt += stack[stackTop - 2];
  stackSrt += " ";
  stackSrt += stack[stackTop - 1];
  stackSrt += " ok>";
  return stackSrt;
}

void push(int num) {
  stack[stackTop] = num;
  stackTop++;
}
int pop() {
  stackTop--;
  int num = stack[stackTop];
  stack[stackTop] = 0;
  return num;
}

void sendWS(String broadcast) {
  webSocket.broadcastTXT(broadcast);
}

void words() {
  String temp = dic;
  do {
    String wordS = selectToMarker(temp, ";");
    Serial.println(wordS);
    temp = deleteBeforeDelimiter(temp, "\r\n");
    sendWS(wordS+";");
    //sendWS("  ");
    sendWS("\r\n");
    //Serial.println(temp);
  } while (temp.length() != 0);
  sendWS("\r\n");
}
