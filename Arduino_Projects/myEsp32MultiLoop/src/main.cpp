#include <Arduino.h>


void FirstTask(void *parameter){
    uint32_t pause = *((uint32_t*)parameter);
    while (true){
      Serial.println("Starte First Task...");
      delay(pause);
    }
 
}
void SecondTask(void *parameter){
    uint32_t pause = *((uint32_t*)parameter);
    while (true){
      Serial.println("Starte Second Task...");
      delay(pause);
    }
 
}
void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}