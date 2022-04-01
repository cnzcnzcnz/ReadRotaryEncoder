
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>
using namespace std;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64

#define inputSw 2
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
volatile boolean turned;

int latestInputCLK;
int latestInputDT;
long timeOfLastDebounce = 0;
double delayOfDebounce = 0.01;


unsigned long asyncDelay = 0;
unsigned long lastButtonPress = 50;
int delayLength = 500;

char cstr[16];

  String menu1 = "menu1";
  String menu2 = "menu2";
  String menu3 = "menu3";
  String menu4 = "menu4";
  String menu5 = "menu5";

// String headerMenu = "Arduino DSP Menu";

// String menu[5] = {
//   "Menu 1",
//   "Menu 2",
//   "Menu 3",
//   "Menu 4",
//   "Menu 5"
// };

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  pinMode(inputSw, INPUT_PULLUP);
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
  attachInterrupt(1, rotaryDetect, CHANGE);

  latestInputCLK = digitalRead(inputClk);
  latestInputDT = digitalRead(inputDt);


    while(1) {
  // readSwitch();
  // showMenu();
  // readRotaryEncoder();
  // readDigitalRead();
  anotherRotaryChecker();
  showMenu();
  }

}

void anotherRotaryChecker(void){
  if((millis() - timeOfLastDebounce) > delayOfDebounce){
    checkRotary();

    latestInputCLK = digitalRead(inputClk);
    latestInputDT = digitalRead(inputDt);

    timeOfLastDebounce = millis();
  }
}

void rotaryDetect(void) {
  turned=true;
}

void checkRotary(void) {
  if(latestInputCLK == 0 && latestInputDT == 1){
    if(digitalRead(inputClk) == 1 && digitalRead(inputDt) == 0){
      counter++;
      Serial.println(counter);
    } else if(digitalRead(inputClk) == 1 && digitalRead(inputDt) == 1){
      counter--;
      Serial.println(counter);
    }
  } else if(latestInputCLK == 1 && latestInputDT == 0){
    if(digitalRead(inputClk) == 0 && digitalRead(inputDt) == 1){
    counter++;
    Serial.println(counter);
    } else if(digitalRead(inputClk) == 0 && digitalRead(inputDt) == 0){
        counter--;
        Serial.println(counter);
    }
  } else if(latestInputCLK == 1 && latestInputDT == 1){
    if(digitalRead(inputClk) == 0 && digitalRead(inputDt) == 1){
      counter++;
      Serial.println(counter);
    } else if(digitalRead(inputClk) == 0 && digitalRead(inputDt) == 1){
counter--;
Serial.println(counter);
    }
  } else if(latestInputCLK == 0 && latestInputDT == 0){
    if(digitalRead(inputClk) == 1 && digitalRead(inputDt) == 0){
counter++;
Serial.println(counter);
    } else if(digitalRead(inputClk) == 1 && digitalRead(inputDt) == 0){
counter--;
Serial.println(counter);
    }
  }

  // if(digitalRead(inputClk) ^= 0 ^= digitalRead(inputDt) == 1){
  //   Serial.println("CW");
  // } else if(digitalRead(inputClk) == 1 ^= digitalRead(inputDt) == 1){
  //   Serial.println("CCW");
  // }
}

void loop() {
  // display.setTextColor(SSD1306_WHITE);
  // display.setCursor(30,0);
  // display.display();
  // while(1) {
  // readSwitch();
  // // showMenu();
  // readRotaryEncoder();
  // }

}

void readDigitalRead(void){
  // if(turned){
  //   turned = false;
  // Serial.print("InputCLK: ");
  // Serial.println(digitalRead(inputClk));
  // Serial.print("InputDT: ");
  // Serial.println(digitalRead(inputDt));
  // }
  // if(digitalRead(inputClk) ^= digitalRead(inputDt)){
  //   Serial.println("Masuk");
  // }

}

void readSwitch(){
  if(digitalRead(inputSw) == LOW){
    if(millis() - lastButtonPress > 150){
    Serial.println("Tombol ditekan");
    }
lastButtonPress = millis();
  }
  delay(1);

}



void readRotaryEncoder(void){
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

    if(counter < 0){
      counter = 0;
    } else if(counter > 4) {
      counter = 4;
    }
    // displaySomething();
  }
  // showMenu();
currentValue = previousValue;
}

  void displaySomething(void) {
    display.clearDisplay();
    display.setCursor(0, counter);
    display.setTextColor(SSD1306_WHITE);
    display.println(output);
    display.display();
  }

void showMenu(void){
      if(counter < 0){
      counter = 0;
    } else if(counter > 4) {
      counter = 4;
    }

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(30, 0);
    display.print("MAIN MENU");
    display.drawFastHLine(0,10,128,WHITE);

  if(counter == 0){
    displayMenuItem(menu1, 10, true);
    displayMenuItem(menu2, 20, false);
    displayMenuItem(menu3, 30, false);
    displayMenuItem(menu4, 40, false);
    displayMenuItem(menu5, 50, false);
  } else if(counter == 1){
    displayMenuItem(menu1, 10, false);
    displayMenuItem(menu2, 20, true);
    displayMenuItem(menu3, 30, false);
    displayMenuItem(menu4, 40, false);
    displayMenuItem(menu5, 50, false);
  } else if(counter == 2){
    displayMenuItem(menu1, 10, false);
    displayMenuItem(menu2, 20, false);
    displayMenuItem(menu3, 30, true);
    displayMenuItem(menu4, 40, false);
    displayMenuItem(menu5, 50, false);
  } else if(counter == 3){
    displayMenuItem(menu1, 10, false);
    displayMenuItem(menu2, 20, false);
    displayMenuItem(menu3, 30, false);
    displayMenuItem(menu4, 40, true);
    displayMenuItem(menu5, 50, false);
  } else if(counter == 4){
    displayMenuItem(menu1, 10, false);
    displayMenuItem(menu2, 20, false);
    displayMenuItem(menu3, 30, false);
    displayMenuItem(menu4, 40, false);
    displayMenuItem(menu5, 50, true);
  }

  display.display();

}

void displayMenuItem(String item, int position, boolean selected){
  if(selected){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.setCursor(0, position);
  display.print(item);
}
