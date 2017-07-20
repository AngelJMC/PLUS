
//----------------------------------------------------------------
//-- Zowi basic firmware v2 adapted to Otto
//-- (c) BQ. Released under a GPL licencse
//-- 04 December 2015
//-- Authors:  Anita de Prado: ana.deprado@bq.com
//--           Jose Alberca:   jose.alberca@bq.com
//--           Javier Isabel:  javier.isabel@bq.com
//--           Juan Gonzalez (obijuan): juan.gonzalez@bq.com
//--           Irene Sanz : irene.sanz@bq.com
//-----------------------------------------------------------------
//-- Experiment with all the features that Otto has thanks to Zowi!
//-----------------------------------------------------------------
//-- FEBRUARY 2017: modified for OTTO with MAX7219 MATRIX LED module
//-- allows OTTO to display gestures whilst stationary on a desk
//-- Jason Snow
//-----------------------------------------------------------------


#include <BatReader.h>
#include <US.h>
#include "MaxMatrix.h"
MaxMatrix ledmatrix=MaxMatrix(12,10,11, 1); //PIN  12=DIN, PIN 10=CS, PIN 11=CLK

//-- Library to manage external interruptions
#include <EnableInterrupt.h> 

//-- Library to manage serial commands
#include <OttoSerialCommand.h>
OttoSerialCommand SCmd;  //The SerialCommand object

//-- Otto Library
#include <Otto.h>
Otto Otto;  //This is Otto!
 
//---------------------------------------------------------
//-- First step: Configure the pins where the servos are attached
/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         --------------- 
            ||     ||
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/

  #define PIN_YL 2 //servo[0]
  #define PIN_YR 3 //servo[1]
  #define PIN_RL 4 //servo[2]
  #define PIN_RR 5 //servo[3]

//---Otto Buttons
#define PIN_SecondButton 6
#define PIN_ThirdButton 7
// buzzer connected to pin 13

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////

const char programID[]="Otto_todo"; //Each program will have a ID

const char name_fac='$'; //Factory name
const char name_fir='#'; //First name

//-- Movement parameters
int T=1000;              //Initial duration of movement
int moveId=0;            //Number of movement
int moveSize=15;         //Asociated with the height of some movements

//---------------------------------------------------------
//-- Otto has 5 modes:
//--    * MODE = 0: Otto is awaiting  
//--    * MODE = 1: Dancing mode!  
//--    * MODE = 2: Obstacle detector mode  
//--    * MODE = 3: Noise detector mode   
//--    * MODE = 4: OttoPAD or any Teleoperation mode (listening SerialPort). 
//---------------------------------------------------------
volatile int MODE=0; //State of Otto in the principal state machine. 

volatile bool buttonPushed=false;  //Variable to remember when a button has been pushed
volatile bool buttonAPushed=false; //Variable to remember when A button has been pushed
volatile bool buttonBPushed=false; //Variable to remember when B button has been pushed

unsigned long previousMillis=0;

int randomDance=0;
int randomSteps=0;
int gesture = 0;
bool obstacleDetected = false;


///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){

  //Serial communication initialization
  Serial.begin(115200);  

  pinMode(PIN_SecondButton,INPUT); //D6 - ensure pull-down resistors are used
  pinMode(PIN_ThirdButton,INPUT); //D67 - ensure pull-down resistors are used
  
  //Set the servo pins
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
 
  //Uncomment this to set the servo trims manually and save on EEPROM 
    Otto.setTrims(10,-10,3,-9);
    //Otto.setTrims(TRIM_YL, TRIM_YR, TRIM_RL, TRIM_RR);
    //Otto.saveTrimsOnEEPROM(); //Uncomment this only for one upload when you finaly set the trims.
// set up Matrix display
  ledmatrix.init();
  ledmatrix.setIntensity(1);
  //Set a random seed
  randomSeed(analogRead(A6));



  //Otto wake up!
  Otto.sing(S_connection);
  Otto.home();






  previousMillis = millis();

}



///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
         //desktop demo of OTTO gestures every 15 seconds
        // start with a delay of 15 seconds
       delay(2000); 
       Serial.println("Loop");

      
        //select a random number between 1 and 15
      
      gesture = random(1,16);
      // display the relevant gesture for the random number selected
      switch (gesture) {
      case 1: //H 1 
        Otto.playGesture(OttoHappy);
        break;
      case 2: //H 2 
        Otto.playGesture(OttoSuperHappy);
        break;
      case 3: //H 3 
        Otto.playGesture(OttoSad);
        break;
      case 4: //H 4 
        Otto.playGesture(OttoSleeping);
        break;
      case 5: //H 5  
        Otto.playGesture(OttoFart);
        break;
      case 6: //H 6 
        Otto.playGesture(OttoConfused);
        break;
      case 7: //H 7 
        Otto.playGesture(OttoLove);
        break;
      case 8: //H 8 
        Otto.playGesture(OttoAngry);
        break;
      case 9: //H 9  
        Otto.playGesture(OttoFretful);
        break;
      case 10: //H 10
        Otto.playGesture(OttoMagic);
        break;  
      case 11: //H 11
        Otto.playGesture(OttoWave);
        break;   
      case 12: //H 12
        Otto.playGesture(OttoVictory);
        break; 
      case 13: //H 13
        Otto.playGesture(OttoFail);
        break;     
      case 14: //M 17 500 
       Otto.shakeLeg(1,T,1);
        break;
       case 15: //M 18 500 
        Otto.shakeLeg(1,T,-1);
        break;    
    }
          
      
}  




