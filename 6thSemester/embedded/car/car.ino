#include "Wheels.h"
#include "LiquidCrystal_I2C.h"

#define LCDAddress 0x27
#define MMPS 450

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);


Wheels w;
long argIn = 0;
long dist = 0; // in mm
unsigned long t1 = 0;
unsigned long t2 = 0;
int delay2 = 100;

int lspeed = 0;
int rspeed = 0;



void setup() {
    // put your setup code here, to run once:
    w.attach(7,8,5,12,11,10);
    
    Serial.begin(9600);
    Serial.setTimeout(200);

    lcd.init();
    lcd.backlight();
}

void loop() {
    unsigned long t = millis();
    
    argIn = Serial.parseInt(SKIP_ALL);
    
    if (argIn > 0) {
        dist = argIn * 10;
        t1 = t;
        w.setSpeed(200, &lspeed, &rspeed);
        w.forward();
    }

    long new_dist = dist - (long)(t - t1) * MMPS / 1000;

    dist = (new_dist > 0) ? new_dist : 0;

    if (t >= t2 + delay2) {
        t2 += delay2;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(dist);
        lcd.setCursor(0, 1);
        lcd.print(lspeed);
        lcd.setCursor(12, 1);
        lcd.print(rspeed);
    }

    if (dist == 0) {
        w.stop(&lspeed, &rspeed);
    }
}
