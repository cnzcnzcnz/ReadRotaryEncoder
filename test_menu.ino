
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>
using namespace std;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64

#define inputClk 3
#define inputDt 4

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int counter = 0;
int currentValue;
int previousValue;
int maxHeight;
int minHeight;
int state = 0;
String output = "";

unsigned long asyncDelay = 0;
int delayLength = 500;

char cstr[16];

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  pinMode(inputClk, INPUT);
  pinMode(inputDt, INPUT);

  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
        display.setTextColor(SSD1306_WHITE);
      display.setTextSize(1.5);
  display.setCursor(0,0);

  currentValue = digitalRead(inputClk);

  
  // put your setup code here, to run once:

}

void loop() {
    readRotaryEncoder();

    
    // test();
    // test2();
  // put your main code here, to run repeatedly:


}

// void testDisplayMenu(void){
//   const char *menu[5] = {
//   " Menu 1",
//   " Menu 2",
//   " Menu 3",
//   " Menu 4",
//   " Menu 5"
//   }

//   previousValue
// }




void test(void){
    previousValue = digitalRead(inputClk);
  if(currentValue != previousValue){
    if(digitalRead(inputDt) != previousValue){
      counter ++;
      } else {
      counter --;
    }
    if(counter > 0 && counter < 64){
      display.clearDisplay();
      display.write("Position : ");
      display.write(itoa(counter, cstr, 10));
      display.setCursor(0, counter);
      display.display();
      
      // display.write("\n");
    Serial.print(digitalRead(inputDt));
    Serial.print("Position : ");
    Serial.print(counter);
    Serial.println(" ");
    } else if(counter < 4){
      minHeight = counter;
      display.clearDisplay();
      display.write("Maximum value");
      Serial.println("Maximum value");
      display.setCursor(0,minHeight);
      display.display();
      counter = 4;
    } else if(counter > 60) {
      maxHeight = counter;
      display.clearDisplay();
      Serial.println("Maximum value");
      display.write("Maximum value");
      display.setCursor(0,maxHeight);
      display.display();
      counter = 58;
    }
  }
  currentValue = previousValue;
}

void readRotaryEncoder(void){

  // display.clearDisplay();
  // display.setCursor(0,0);
  previousValue = digitalRead(inputClk);
  if(currentValue != previousValue){
    if(digitalRead(inputDt) != previousValue && (state == 0 || state == 1)){
      counter ++;
      state = 1;
      Serial.println("Clockwise");
      output = "Clockwise";
      asyncDelay = millis();
      } else if(digitalRead(inputDt) == previousValue && (state == 0 || state == 2)) {
      counter --;
      state = 2;
      Serial.println("Counter Clockwise");
      output = "Counter Clockwise";
      asyncDelay = millis();
    }
    Serial.println(counter);

    if(millis() > asyncDelay + delayLength){
      asyncDelay+=delayLength;
      state = 0;
    }
    displaySomething();
  }

 

  

  // for(int i = 0; i < 6; i++){
  //   if(counter > -1 && counter < 6){
  //     if(counter == i){
  //       display.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
  //       display.println(menu[i]);
  //     } else {
  //       display.setTextColor(SSD1306_WHITE);
  //       display.println(menu[i]);
  //     }
  //   }
  //   }

  // display.display();
currentValue = previousValue;
}

  void displaySomething(void) {
    display.clearDisplay();
    display.setCursor(0, counter);
    display.setTextColor(SSD1306_WHITE);
    display.println(output);
    display.display();
  } 

void test2(void){
    previousValue = digitalRead(inputClk);
  if(currentValue != previousValue){
    if(digitalRead(inputDt) != previousValue){
      counter ++;
      } else {
      counter --;
    }
    Serial.println(counter);
  }
  currentValue = previousValue;
}

