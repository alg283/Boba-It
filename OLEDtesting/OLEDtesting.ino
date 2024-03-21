#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

const int OLED_MOSI = 9;
const int OLED_CLK = 10;
const int OLED_DC = 11;
const int OLED_CS = 12;
const int OLED_RST = 13;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
}

void loop() {
  // put your main code here, to run repeatedly:

  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("HELLO WORLD!");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("GOODBYE WORLD!");
  display.display();
  delay(2000);

}
