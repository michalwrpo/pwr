#include "ir_remote_codes.h"
#include "logger.h"
#include "Wheels.h"

#include <IRremote.h>
#include <SD.h>
#include <Servo.h>

#define LCDAddress 0x27
#define MMPS 450

#define TRIG A1
#define ECHO A2

#define IR_PIN 3
#define SERVO 9
#define SD_PIN 10

Servo servo;
Wheels w;

long look_delay = 500;
long press_delay = 250;
unsigned long t_move_tick = 0;
unsigned long t_lookl = 0;
unsigned long t_look = look_delay / 2;
unsigned long t_lookr = look_delay;
unsigned long t_press = 0;
bool blocked = false;
bool going = false;
bool newMode = false;
bool just_read = false;

long angle = 90;
long distance = 0;
long dr = 0, dc = 0, dl = 0;

enum IRRemoteCode ir_code = 0;

void setup() {
    w.attach(7,8,5,2,4,6);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    servo.attach(SERVO);
   
    Serial.begin(9600);
    Serial.setTimeout(200);

    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

    w.setSpeed(200);

    if (!SD.begin(SD_PIN)) {
        Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
        while (1); // don't do anything more:
    }

    Logger::init("logs.txt");

    Serial.println("SD card initialized.");

    Logger::log("Initialized");
}

void loop() {
    if (IrReceiver.decode()) {
        int new_ir_code = IrReceiver.decodedIRData.command;
        if (new_ir_code) {
            ir_code = new_ir_code;

            if (ir_code != IR3) {
                just_read = false;
            }
            if (new_ir_code != ir_code) {
                Logger::partial_log("Pressed");
                Logger::log(new_ir_code);
                newMode = true;
            }
        }
        IrReceiver.resume();
        clearTimes();
    }

    unsigned long t = millis();

    switch (ir_code) {
    case IR1:
    {
        if (newMode) {
            Logger::log("Mode: wander");
            newMode = false;
        }
        
        w.forward();

        if (dr < 30 || dc < 30 || dl < 30) {
            blocked = true;
            if (dc < 30) dodge(1000);
            else dodge(500);
            w.forward();
            blocked = false;
            dr = dc = dl = 40;
        }

        if (!blocked && t >= t_lookl + 2 * look_delay) {
            t_lookl += 2 * look_delay;
            angle = 120;
            lookAndTellDistance();
            dl = distance;
        }

        if (!blocked && t >= t_look + look_delay) {
            t_look += look_delay;
            angle = 90;
            lookAndTellDistance();
            dc = distance;
        }

        if (!blocked && t >= t_lookr + 2 * look_delay) {
            t_lookr += 2 * look_delay;
            angle = 60;
            lookAndTellDistance();
            dr = distance;
        }

        break;
    }
    case IR2:
    {
        if (newMode) {
            Logger::log("Mode: dog");
            newMode = false;
        }

        if (t >= t_look + look_delay / 2) {
            t_look = t;
            angle = 90;
            lookAndTellDistance();
            dc = distance;
        }

        if (dc > 60) {
            w.setSpeed(200);
            w.forward();
        } else if (dc > 42) {
            w.setSpeed(120);
            w.forward();
        } else if (dc > 37) {
            w.stop();
        } else if (dc > 20) {
            w.setSpeed(120);
            w.back();
        } else {
            w.setSpeed(200);
            w.back();
        }
        
        break;
    }
    case IR3:
    {
        ir_code = 0;
        w.stop();
        if (!just_read) {
            Logger::read();
            delay(250);
            just_read = true;
        }
        break;
    }
    case IRup:
        if (t >= t_press + press_delay) IRNoPress();
        going = true;

        w.setSpeed(200);
        w.forward();
        break;
    case IRdown:
        if (t >= t_press + press_delay) IRNoPress();
        going = true;

        w.setSpeed(200);
        w.back();
        break;
    case IRleft:
        if (t >= t_press + press_delay) IRNoPress();
        going = true;

        w.stopLeft();
        w.setSpeed(200);
        w.forwardRight();
        break;
    case IRright:
        if (t >= t_press + press_delay) IRNoPress();
        going = true;

        w.stopRight();
        w.setSpeed(200);
        w.forwardLeft();
        break;

    case IRok:
        w.stop();
        break;
    
    default:
        if (going && t >= t_press + press_delay) IRNoPress();
        break;
    }
}

void clearTimes() {
    unsigned long t = millis();
    t_move_tick = t;
    t_lookl = t;
    t_look = t + look_delay / 2;
    t_lookr = t + look_delay;
    t_press = t;
    blocked = false;
}

void IRNoPress() {
    going = false;
    ir_code = 0;
    w.stop();
}

void lookAndTellDistance() {
    unsigned long tot;

    servo.write(angle);

    digitalWrite(TRIG, HIGH);
    delay(10);
    digitalWrite(TRIG, LOW);
    tot = pulseIn(ECHO, HIGH);

    distance = tot/59;
    Logger::partial_log("Measured distance");
    Logger::log(distance);
}

void dodge(int time) {
    Logger::log("Evading object");
    int process_delay = 200;

    w.stop();
    angle = 30;
    lookAndTellDistance();
    long rdist1 = distance;
    delay(process_delay);
    angle = 60;
    lookAndTellDistance();
    long rdist2 = distance;
    delay(process_delay);
    angle = 120;
    lookAndTellDistance();
    long ldist1 = distance;
    delay(process_delay);
    angle = 150;
    lookAndTellDistance();
    long ldist2 = distance;

    angle = 90;

    if ((rdist1 + rdist2) > (ldist1 + ldist2)) {
        w.backRight();
    } else {
        w.backLeft();
    }

    delay(time);
    
    w.stop();
}
