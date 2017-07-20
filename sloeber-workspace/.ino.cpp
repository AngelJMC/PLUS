#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-07-20 18:18:58

#include "Arduino.h"
#include <BatReader.h>
#include <US.h>
#include "MaxMatrix.h"
#include <EnableInterrupt.h>
#include <OttoSerialCommand.h>
#include <Otto.h>
void setup();
void loop() ;
void secondButtonPushed();
void thirdButtonPushed();
void obstacleDetector();
void receiveStop();
void receiveLED();
void recieveBuzzer();
void receiveTrims();
void receiveServo();
void receiveMovement();
void move(int moveId);
void receiveGesture();
void receiveSing();
void receiveName();
void requestName();
void requestDistance();
void requestNoise();
void requestBattery();
void requestProgramId();
void sendAck();
void sendFinalAck();
void OttoLowBatteryAlarm();
void OttoSleeping_withInterrupts();

#include "Otto.ino"


#endif
