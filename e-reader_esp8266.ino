#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C // find the correct address later
#define RESET_PIN -1 // idk why either, maybe if the OLED doesnt have a reset pin

#define BUTTONDOWN 12 // button that is for "down"
#define BUTTONUP 14 // button that is for "up"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, RESET_PIN);

char longText[] = "Regulation: Public Private Participation in Nuclear Power Development Private corporations, including domestic and foreign-owned companies, may participate in: a. Design, construction, financing, operation, and decommissioning of Nuclear Power Plants b. Research, development, and demonstration of advanced reactor technologies. Foreign entities shall operate through a locally incorporated special-purpose company registered in Indonesia. Nuclear Power Plants may be developed under Public–Private Partnership schemes, including: a. Build–Own–Operate (BOO) b. Build–Operate–Transfer (BOT) c. Joint venture with state-owned enterprises. Ownership of nuclear materials remains under state control at all times Qualified private nuclear projects may receive: a. Tax holidays and import-duty exemptions; b. Priority grid access; c. Government-backed power purchase agreements (PPAs). Nuclear power shall be recognized as a strategic clean energy investment. ";
int textCursor = 0;
const int textGrabLength = 20;
const int bufferSize = textGrabLength + 1;
int longTextLength = strlen(longText);

char textBuffer[bufferSize]; 

char line1[bufferSize];
char line2[bufferSize];
char line3[bufferSize];

void initializeText();
void nextText();
void previousText();
void updateTextUp();
void updateTextDown();

// Debouncing logic
unsigned long lastPrintTime = 0;
const long printInterval = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // loading text buffer
  display.display();
  delay(1000);
  display.clearDisplay();

  // Fonts etc
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setTextSize(1);
  display.setTextWrap(true);

  // Button Pins
  pinMode(BUTTONDOWN, INPUT_PULLUP);
  pinMode(BUTTONUP, INPUT_PULLUP);

  // Text Logic
  initializeText();
}

void loop() {
  // Button Logic
  int buttonUpState = digitalRead(BUTTONUP);
  int buttonDownState = digitalRead(BUTTONDOWN);

  if (millis() - lastPrintTime >= printInterval){
    if (buttonDownState == LOW){
      if (textCursor <= longTextLength){
        nextText();
        updateTextDown();
      }
      Serial.println("DOWN button pressed!");
    }
    else if (buttonUpState == LOW){
      if ((textCursor > textGrabLength * 3)){
        previousText();
        updateTextUp();
      }
      Serial.println("UP button pressed!");
    }
    lastPrintTime = millis();
  }
  

  display.clearDisplay();
  printText();
  display.display();
}

// using functions

void initializeText(void){
  nextText();
  strncpy(line1, textBuffer, textGrabLength);
  nextText();
  strncpy(line2, textBuffer, textGrabLength);
  nextText();
  strncpy(line3, textBuffer, textGrabLength);

  // clear the buffer
  Serial.print("Text buffer after intialization:" );
  Serial.println(textBuffer);
}

void nextText(void){
  for (int i = 0; i < textGrabLength; i++){
    textBuffer[i] = longText[textCursor+i];
  }
  textCursor = textCursor + textGrabLength;
}

void previousText(void){
  for (int i = 0; i < textGrabLength; i++){
    textBuffer[i] = longText[textCursor-(4*textGrabLength)+i];
  }
  textCursor = textCursor - textGrabLength;
}

void updateTextDown(void){
  strncpy(line1, line2, textGrabLength);
  strncpy(line2, line3, textGrabLength);
  strncpy(line3, textBuffer, textGrabLength);
}

void updateTextUp(void){
  strncpy(line3, line2, textGrabLength);
  strncpy(line2, line1, textGrabLength);
  strncpy(line1, textBuffer, textGrabLength);
}



void printText(void){
  display.setCursor(0, 0);
  display.write(line1);
  // Serial.println(line1);

  display.setCursor(0, 11);
  display.write(line2);
  // Serial.println(line2);

  display.setCursor(0, 22);
  display.write(line3);
  // Serial.println(line3);
}