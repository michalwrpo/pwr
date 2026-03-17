#include <Arduino.h>

#include "Wheels.h"

#define SET_MOVEMENT(side,f,b) digitalWrite( side[0], f);\
                               digitalWrite( side[1], b)

Wheels::Wheels() 
{ }

signed char ldir = 1;
signed char rdir = 1;

void Wheels::attachRight(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsRight[0] = pF;
    this->pinsRight[1] = pB;
    this->pinsRight[2] = pS;
}


void Wheels::attachLeft(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsLeft[0] = pF;
    this->pinsLeft[1] = pB;
    this->pinsLeft[2] = pS;
}

void Wheels::setSpeedRight(uint8_t s, int* rspeed)
{
    analogWrite(this->pinsRight[2], s);
    *rspeed = s * rdir;
}

void Wheels::setSpeedLeft(uint8_t s, int* lspeed)
{
    analogWrite(this->pinsLeft[2], s);
    *lspeed = s * ldir;
}

void Wheels::setSpeed(uint8_t s, int* lspeed, int* rspeed)
{
    setSpeedLeft(s, lspeed);
    setSpeedRight(s, rspeed);
}

void Wheels::attach(int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
{
    this->attachRight(pRF, pRB, pRS);
    this->attachLeft(pLF, pLB, pLS);
}

void Wheels::forwardLeft() 
{
    SET_MOVEMENT(pinsLeft, HIGH, LOW);
    ldir = 1;
}

void Wheels::forwardRight() 
{
    SET_MOVEMENT(pinsRight, HIGH, LOW);
    rdir = 1;
}

void Wheels::backLeft()
{
    SET_MOVEMENT(pinsLeft, LOW, HIGH);
    ldir = -1;
}

void Wheels::backRight()
{
    SET_MOVEMENT(pinsRight, LOW, HIGH);
    rdir = -1;
}

void Wheels::forward()
{
    this->forwardLeft();
    this->forwardRight();
}

void Wheels::back()
{
    this->backLeft();
    this->backRight();
}

void Wheels::stopLeft(int* lspeed)
{
    SET_MOVEMENT(pinsLeft, LOW, LOW);
    *lspeed = 0;
}

void Wheels::stopRight(int* rspeed)
{
    SET_MOVEMENT(pinsRight, LOW, LOW);
    *rspeed = 0;
}

void Wheels::stop(int* lspeed, int* rspeed)
{
    this->stopLeft(lspeed);
    this->stopRight(rspeed);
}

// void Wheels::goForward(int cm) {
//     this->forward();
//     // this->setSpeed(200);
//     delay(cm * 27);
//     this->stop();
// }

// void Wheels::goBack(int cm) {
//     this->back();
//     // this->setSpeed(200);
//     delay(cm * 27);
//     this->stop();
// }