#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <LedControl.h>
#include <LiquidCrystal_I2C.h>
#include <RX9QR.h>
#include <SoundSensor.h>
#include <Stepper.h>
#include <StepperMulti.h>
#include <TM1637Display.h>
#include <core_build_options.h>
#include <font.h>
#include <swRTC.h>


LedControl lc = LedControl(10, 12, 11, 1);

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false);
  lc.clearDisplay(0);

  lc.setIntensity(0, 1);
  lc.setRowOrColumn(0, 1, 0, "11111111");
  lc.drawLEDMatrix("0000000000110100001100100000001000000010001100100011010000000000");
  loop();
  
  while(1){
  lc.drawScrollLEDMatrix("0000000000110100001100100000001000000010001100100011010000000000");
}
}

void loop() {
  // put your main code here, to run repeatedly:
  lc.clearDisplay(0);
  for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
      lc.setLed(0,row,col,true);
      delay(200);
    }
  }
}
