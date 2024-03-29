
//If you found my video helpful, please SUBSCRIBE:  https://www.youtube.com/channel/UCKp1MzuAceJnDqAvsZl_46g
//The code belongs to the following tutorial video: https://youtu.be/AR0un3kg-iM
//example s 2000 4000 == 2000 steps (5 revolution with 400 step/rev microstepping) and 400 steps/s == 1 rev/sec speed

#include <AccelStepper.h>
#include <Servo.h>

#include <PS3USB.h>
#include <Thread.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
//#define DEBUG_REGIME 1 // slows the program == motors work slower
#define JOYSTICKACTIVATION // comment if want to remove joystick
#define JOYSTICKDEBUG // prints joystick logs
/////////////////////////// PS3 through USB settings


USB Usb;
/* You can create the instance of the class in two ways */
PS3USB PS3(&Usb); // This will just create the instance
//PS3USB PS3(&Usb,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printAngle;
uint8_t state = 0;

int isJoystickActivated = 0;
///////////////////////////// END OF PS3 SETTINGS
// 1 == 0 -8000 8000
// 2
// 3 -- 0 -25000 25000
// blue blue
//red red
//green orange
//blk blk
//s -1000 1000 0 0 -10000 1600 -1000 1000 -1000 1000
struct command
{
  long angle = 0;
  int rotation_speed = 0;
  int axis = 0;
};
const int numberOfSteppers = 6;
const int commandsNum = numberOfSteppers;
int shouldPermanentlyRun[numberOfSteppers] = {0, 0, 0, 0, 0};
int shouldPermanentlyRunSpeed[numberOfSteppers] = {3200, 3200, 3200, 1600, 1600};
int stepperDistanceWasSet[numberOfSteppers] = {0, 0, 0, 0, 0, 0};
const int current_step_multiplier[numberOfSteppers] = {3, 2, 2, 2, 2, 1}; // where 1 is 800, 2 is 1600, the logic is clear?
const int max_speed [numberOfSteppers] = {3200, 3200, 3200, 3200, 3200,1600};
int speed_var = 1600;
//const int max_speed [5] = {speed_var, speed_var, speed_var, speed_var, speed_var};

/////////////////////////////// ?      31000  -62000 ?        ?
const long stepsToHome[numberOfSteppers] = { -14200, 64000, -70000, 20000, 8000, 800}; // step == 1.8 / 4
////////////////////////                    -29500
////////////////////////                    30000 to reach limit, 32000 to get back
bool isSwitchActivated[numberOfSteppers] = { false, false, false, false, false}; // step == 1.8 / 4
int startHomingFrom = 1; // skip 1 axis


//steps per degree ==
// 1 axis == 8000/90 == 88 steps per 1 degree
// 2 axis == 22000/45 == 488 steps per 1 degree
// 3 axis == 31000/45 == 688 steps per 1 degree
// 4 axis == 6400/90 == 71 steps per 1 degree
// 5 axis == 2500/45 = 11 steps per 1 degree
struct stepper_parameters
{
  bool isDual;
  AccelStepper* stepper1;
  AccelStepper* stepper2;
  command command1;
  command command2; // if dual
  int dir_pin1;
  long step_pin1;
  int dir_pin2;
  long step_pin2;
  bool haveSameSign;
  bool isFirstPositive;
  int increment_step;
  int max_acc = 400;
  int max_speed = 400;
  int change_direction = false;
};

bool mcpn_flag = false;
int  mcpn_dir[] = {0, 0, 0, 0, 0};
stepper_parameters steppers[numberOfSteppers];



// s -500 400 -1500 400 -1000 500
//  s -0 800 -0 2000 -0 1000
// s -0 0 -0 0 3000 800

// s 2000 400 10000 1600 -30000 6400 800 400 1500 400
// s 0 250 0 1600 0 6400 0 400 0 400


long receivedMMdistance = 0; //distance in mm from the computer
long receivedDelay = 0; //delay between two steps, received from the computer

long receivedMMdistance2 = 0; //distance in mm from the computer
long receivedDelay2 = 0; //delay between two steps, received from the computer

long receivedMMdistance2_1 = 0; //distance in mm from the computer
long receivedDelay2_1 = 0; //delay between two steps, received from the computer

long receivedMMdistance3 = 0; //distance in mm from the computer
long receivedDelay3 = 0; //delay between two steps, received from the computer

long receivedMMdistance3_1 = 0; //distance in mm from the computer
long receivedDelay3_1 = 0; //delay between two steps, received from the computer

long receivedMMdistance4 = 0; //distance in mm from the computer
long receivedDelay4 = 0; //delay between two steps, received from the computer

long receivedMMdistance5 = 0; //distance in mm from the computer
long receivedDelay5 = 0; //delay between two steps, received from the computer

long receivedAcceleration = 0; //acceleration value from computer
char receivedCommand; //character for commands
/* s = Start (CCW) // needs steps and speed values
   o = open (CCW) // needs steps and speed values
   c = close (CW) //needs steps and speed values
   a = set acceleration // needs acceleration value
   n = stop right now! // just the 'n' is needed
*/

// 1 + cw - ccw [4000 -2000]    stoper = [ 2000. -3550.] homing ccw
// 2 + cw - ccw [16000 -16000] stoper = [-22800 21200.] homing cw
// 3 + cw - ccw [40000 -40000] stoper = [ -13800. 17000.] homing cw
// 4 + cw - ccw [800 -800] stoper=[ -805 830.]  homing cw
// 5 + cw - ccw [1200 -1200] stoper=[ -1800 1650.] homing cw

// 800 400 800

bool newData, runallowed = false; // booleans for new data from serial, and runallowed flag

// 1 == 0 1100 -1100





Servo servo1;

const int home_switch[numberOfSteppers] = {22, 23, 24, 25, 26, 27};

// s -1000 400 -1500 400 1500 400
// s -1000 500 2500 1000 6000 1000
// s 0 400 0 1000 0 1000


void setDefaultParametersForSwitches() {
  for (int i = 0; i < numberOfSteppers; i++)
  {
    isSwitchActivated[i] = false;
  }
}
void setDefaultParametersForSteppers() {
  for (int i = 0; i < numberOfSteppers; i++)
  {
    if (steppers[i].isDual)
    {
      steppers[i].stepper1->setCurrentPosition(0);
      steppers[i].stepper1->setMaxSpeed(max_speed[i]);
      steppers[i].stepper1->setAcceleration(max_speed[i]);
      steppers[i].stepper2->setCurrentPosition(0);
      steppers[i].stepper2->setMaxSpeed(max_speed[i]);
      steppers[i].stepper2->setAcceleration(max_speed[i]);
    } else
    {
      steppers[i].stepper1->setCurrentPosition(0);
      steppers[i].stepper1->setMaxSpeed(max_speed[i]);
      steppers[i].stepper1->setAcceleration(max_speed[i]);
    }
  }
}
void stopMovement() {
  for (int i = 0; i < numberOfSteppers; i++)
  {
    if (steppers[i].isDual)
    {
      steppers[i].stepper1->moveTo( steppers[i].stepper1->currentPosition());
      steppers[i].stepper2->moveTo( steppers[i].stepper1->currentPosition());
    } else
    {
      steppers[i].stepper1->moveTo( steppers[i].stepper1->currentPosition());
    }
  }
}
void enableSteppers()
{
  for (int i = 0; i < numberOfSteppers; i++)
  {
    if (steppers[i].isDual)
    {
      steppers[i].stepper1->enableOutputs();
      steppers[i].stepper2->enableOutputs();
    } else
    {
      steppers[i].stepper1->enableOutputs();
    }
  }
}

void runSteppers()
{

  for (int i = 0; i < numberOfSteppers; i++)
  {
    //    if(shouldPermanentlyRun[i] == 1)
    //    {
    //         Serial.println("IN HERE!!!1111111111111111111111111 ");
    //
    //   //    steppers[i].stepper1->setMaxSpeed(shouldPermanentlyRunSpeed[i]);
    //    //   steppers[i].stepper1->setSpeed(shouldPermanentlyRunSpeed[i]);
    //    //   steppers[i].stepper1->runSpeed();
    //
    //    }else if(shouldPermanentlyRun[i] == -1)
    //    {
    //
    //         Serial.println("IN HERE!!!------------------------1111111111111111111111111 ");
    //   //    steppers[i].stepper1->setMaxSpeed(-shouldPermanentlyRunSpeed[i]);
    //   //    steppers[i].stepper1->setSpeed(-shouldPermanentlyRunSpeed[i]);
    //   //    steppers[i].stepper1->runSpeed();
    //    }
    if (steppers[i].isDual)
    {
      steppers[i].stepper1->run();
      steppers[i].stepper2->run();
    } else
    {
      steppers[i].stepper1->run();
      //Serial.println(String(steppers[i].stepper1->distanceToGo()) + " =  dtG.");
    }
  }
}

void disableSteppers()
{
  for (int i = 0; i < numberOfSteppers; i++)
  {
    if (steppers[i].isDual)
    {
      steppers[i].stepper1->disableOutputs();
      steppers[i].stepper2->disableOutputs();
    } else
    {
      steppers[i].stepper1->disableOutputs();
    }
  }
}

void setSpeedAndAcceleration()///
{
  for (int i = 0; i < numberOfSteppers; i++)
  {
    if (steppers[i].isDual)
    {
      steppers[i].stepper1->setAcceleration(max_speed[i]);
      steppers[i].stepper1->setMaxSpeed(max_speed[i]);
      steppers[i].stepper2->setAcceleration(max_speed[i]);
      steppers[i].stepper2->setMaxSpeed(max_speed[i]);
    } else
    {
      steppers[i].stepper1->setAcceleration(max_speed[i]);
      steppers[i].stepper1->setMaxSpeed(max_speed[i]);
    }
  }
}

command getValues(String data, char separator)
{
  int found = 0;
  int strIndex[10];
  int maxIndex = data.length();
  command com;

  for (int i = 0, j = 0; i < maxIndex; i++) {
    if (data.charAt(i) == separator) {
      found++;
      strIndex[j] = i;
      j++;
    }
  }

  com.angle = data.substring(strIndex[2], data.length()).toInt();
  com.axis = data.substring(strIndex[0], strIndex[1]).toInt();

  if (found != 3 ) Serial.println("BAD INPUT!");

  return com;
};

void printReceivedCommands(command *coms)
{
  for (int i = 0; i < commandsNum; i++)
  {
    Serial.print(String(coms[i].angle) + " " + String(coms[i].rotation_speed) + " ");

  }
  Serial.println();
}

void getIndexArray(int* separatorIndex , String data, char separator, int &found)
{
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == separator) {
      separatorIndex[found] = i;
      //Serial.print(String(separatorIndex[found]) + " ");
      found++;
    }
  }
  if (found % 2 != 0) Serial.println("BAD INPUT!"); //print a message
}

//s 200 233 0 0 0 0 0 0 444 456
void parseValue(String data, char separator, command * com)
{
  int found = 0;
  int * separatorIndex = new int[numberOfSteppers*2];
  getIndexArray(separatorIndex, data, separator, found);
  int counter = 0;
  for (int i = 0; i < found; i++)
  {

    if (i == found - 1) {
      com[counter].rotation_speed = data.substring(separatorIndex[i], data.length()).toInt();
    }
    else {
      if (i % 2 == 0) {
        com[counter].angle = data.substring(separatorIndex[i], separatorIndex[i + 1]).toInt();
        Serial.println(String(com[counter].angle) + "val of angle, counter = " + String(counter));
      }
      else com[counter].rotation_speed = data.substring(separatorIndex[i], separatorIndex[i + 1]).toInt();
    }
    if (i % 2 != 0) counter++;
  }
}



void setLargeMovement(int axis, int sign)
{
  //steppers[axis].stepper1->setAcceleration(max_speed[axis]);
  steppers[axis].stepper1->moveTo(100000 * sign);
  //steppers[axis].stepper1->setMaxSpeed(max_speed[axis]);
  stepperDistanceWasSet[axis] = 1;
}

void stopStepperSaveCurrentPosition(int axis)
{
  //steppers[axis].stepper1->setMaxSpeed(max_speed[axis]);
  //steppers[axis].stepper1->setAcceleration(max_speed[axis]);
  steppers[axis].stepper1->setCurrentPosition(steppers[axis].stepper1->currentPosition());
  stepperDistanceWasSet[axis] = 0;
}

void debugAxisTargetCurrentToGoPositions(int axis)
{
  Serial.print("Debugging of axis: ");
  Serial.println(axis);
  Serial.println("TARGET POSITION & CURRENT POSITION & DISTANCE TO GO: ");
  Serial.println(steppers[axis].stepper1->targetPosition());
  Serial.println(steppers[axis].stepper1->currentPosition());
  Serial.println(steppers[axis].stepper1->distanceToGo());
}
void checkJoystickButtons()
{
  Usb.Task();
  runallowed = true; //allow running
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {

    if (PS3.getButtonClick(PS))
    {
      Serial.print(F("\r\nPS, state is: "));

      if (isJoystickActivated == 0)
        isJoystickActivated = 1; else if (isJoystickActivated == 1)
        isJoystickActivated = 2; else if (isJoystickActivated == 2)
        isJoystickActivated = 0;
      Serial.println(isJoystickActivated);
    }
    /////////////////////////////////////////// ANGLE CONTROL STATE
    //Serial.println(isJoystickActivated);
    if (isJoystickActivated == 1)
    {
      // dont display init position or will be the mess
      if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nLeftHatX: "));
        Serial.print(PS3.getAnalogHat(LeftHatX));
        Serial.print(F("\tLeftHatY: "));
        Serial.println(PS3.getAnalogHat(LeftHatY));
#endif
        if (PS3.getAnalogHat(LeftHatY) == 0)
        {

          if (stepperDistanceWasSet[0] == 0)
          {
            setLargeMovement(0, -1);
          }
        }
        else if (PS3.getAnalogHat(LeftHatY) == 255)
        {

          if (stepperDistanceWasSet[0] == 0)
          {
            setLargeMovement(0, 1);
          }
        } else {
          stopStepperSaveCurrentPosition(0);
        }

        //debugAxisTargetCurrentToGoPositions(0);

        if (PS3.PS3Connected) { // The Navigation controller only have one joystick
#ifdef JOYSTICKDEBUG
          Serial.print(F("\tRightHatX: "));
          Serial.print(PS3.getAnalogHat(RightHatX));
          Serial.print(F("\tRightHatY: "));
          Serial.print(PS3.getAnalogHat(RightHatY));
#endif
        }
        //////////// SECOND AXIS
        if (PS3.getAnalogHat(RightHatY) == 0)
        {
#ifdef DEBUG_REGIME
          Serial.println("1 is ZERO");
#endif
          if (stepperDistanceWasSet[1] == 0)
          {
            setLargeMovement(1, 1);
          }
        }
        else if (PS3.getAnalogHat(RightHatY) == 255)
        {
          if (stepperDistanceWasSet[1] == 0)
          {
            setLargeMovement(1, -1);
          }
        } else {
          stopStepperSaveCurrentPosition(1);
        }
        //debugAxisTargetCurrentToGoPositions(1);
        //////////////////// END SECOND AXIS
      }

      /////////////////////////5 axis
      if (PS3.getButtonPress(TRIANGLE))
      {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nTraingle"));
#endif JOYSTICKDEBUG
        setLargeMovement(4, 1);
      } else if (PS3.getButtonPress(CROSS))
      {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nCross"));
#endif JOYSTICKDEBUG
        setLargeMovement(4, -1);
      } else
      {
        stopStepperSaveCurrentPosition(4);
      }
      /////////////////////////5 axis end

      /////////////////////////6 axis
      if (PS3.getButtonPress(SQUARE))
      {
        #ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nSquare"));
        #endif JOYSTICKDEBUG
        setLargeMovement(5, -1);
      }else if (PS3.getButtonPress(CIRCLE))
      {
      #ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nCircle"));
      #endif JOYSTICKDEBUG
      setLargeMovement(5, 1);
      }else
      {
        stopStepperSaveCurrentPosition(5);
      }
      
      /////////////////////////3 axis
      if (PS3.getButtonPress(UP)) {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nUp"));
#endif JOYSTICKDEBUG
        setLargeMovement(2, 1);
        //        PS3.setLedOff();
        //        PS3.setLedOn(LED4);
      } else if (PS3.getButtonPress(DOWN)) {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nDown"));
#endif JOYSTICKDEBUG
        setLargeMovement(2, -1);
        //        PS3.setLedOff();
        //        PS3.setLedOn(LED2);
      } else
      {
        stopStepperSaveCurrentPosition(2);
      }
      /////////////////////////3 axis end
      /////////////////////////4 axis
      if (PS3.getButtonPress(LEFT)) {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nLeft"));
#endif JOYSTICKDEBUG
        setLargeMovement(3, -1);
        //        PS3.setLedOff();
        //        PS3.setLedOn(LED3);
      } else if (PS3.getButtonPress(RIGHT)) {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nRight"));
#endif JOYSTICKDEBUG
        setLargeMovement(3, 1);
        //        PS3.setLedOff();
        //        PS3.setLedOn(LED1);
      } else
      {
        stopStepperSaveCurrentPosition(3);
      }
      /////////////////////////4 axis end

      // Analog button values can be read from almost all buttons
      if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nL2: "));
        Serial.print(PS3.getAnalogButton(L2));
#endif
        if (!PS3.PS3NavigationConnected) {
#ifdef JOYSTICKDEBUG
          Serial.print(F("\tR2: "));
          Serial.print(PS3.getAnalogButton(R2));
#endif
        }
      }

      if (PS3.getButtonClick(L1))
        Serial.print(F("\r\nL1"));
      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (PS3.getButtonClick(R1))
        Serial.print(F("\r\nR1"));
      if (PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
      if (printAngle) {
        Serial.print(F("\r\nPitch: "));
        Serial.print(PS3.getAngle(Pitch));
        Serial.print(F("\tRoll: "));
        Serial.print(PS3.getAngle(Roll));
      }
      /////////////////////////////////////////// XYZ CONTROL STATE
    } else if (isJoystickActivated == 2)
    {
      //    Serial.println("State 2 == XYZ.");
      int coordinateStep = 10;
      ////////////////////////////////////X COORDINATE
      if (PS3.getButtonPress(UP)) {
#ifdef JOYSTICKDEBUG
        Serial.println(F("\r\nUp"));
#endif JOYSTICKDEBUG
        Serial.print("X ");
        Serial.println(coordinateStep);

        //setLargeMovement(2, 1);
        //        PS3.setLedOff();
        //        PS3.setLedOn(LED4);

      } else if (PS3.getButtonPress(DOWN)) {
#ifdef JOYSTICKDEBUG
        Serial.println(F("\r\nDown"));
#endif JOYSTICKDEBUG
        Serial.print("X -");
        Serial.println(coordinateStep);

        //setLargeMovement(2, -1);
        //        PS3.setLedOff();
        //        PS3.setLedOn(LED2);
      }
      /////////////////////////3 axis end
      /////////////////////////4 axis
      ////////////////////////////////////Y COORDINATE
      if (PS3.getButtonPress(LEFT)) {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nLeft"));
#endif JOYSTICKDEBUG
        setLargeMovement(3, -1);
        //        PS3.setLedOff();
        //        PS3.setLedOn(LED3);
      } else if (PS3.getButtonPress(RIGHT)) {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nRight"));
#endif JOYSTICKDEBUG
        setLargeMovement(3, 1);
        //        PS3.setLedOff();
        //        PS3.setLedOn(LED1);
      } else
      {
        stopStepperSaveCurrentPosition(3);
      }
      ////////////////////////////////////Z COORDINATE
      if (PS3.getButtonPress(TRIANGLE))
      {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nTraingle"));
#endif JOYSTICKDEBUG
        setLargeMovement(4, 1);
      } else if (PS3.getButtonPress(CROSS))
      {
#ifdef JOYSTICKDEBUG
        Serial.print(F("\r\nCross"));
#endif JOYSTICKDEBUG
        setLargeMovement(4, -1);
      } else
      {
        stopStepperSaveCurrentPosition(4);
      }
    }
  }
}

Thread threadCheckJoystick = Thread();
void setup()
{
#ifdef JOYSTICKACTIVATION
  threadCheckJoystick.onRun(checkJoystickButtons);
  threadCheckJoystick.setInterval(50);

  /////////////////////////// PS3 settings
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
#endif
  /////////////////////////// end of PS3 settings
  steppers[0].dir_pin1 = 40;
  steppers[0].step_pin1 = 41;
  steppers[0].isDual = false;
  steppers[0].increment_step = 50;
  steppers[0].max_speed = 800;
  steppers[0].change_direction = true;
  steppers[1].dir_pin1 = 38;
  steppers[1].step_pin1 = 39;
  steppers[1].increment_step = 200;
  //  steppers[1].dir_pin2 = 26;
  //  steppers[1].step_pin2 = 27;
  steppers[1].isDual = false;
  steppers[1].max_speed = 800;
  steppers[1].change_direction = false;
  steppers[2].dir_pin1 = 36;
  steppers[2].step_pin1 = 37;
  //  steppers[2].dir_pin2 = 12;
  //  steppers[2].step_pin2 = 13;
  steppers[2].increment_step = 200;
  steppers[2].isDual = false;
  steppers[2].max_speed = 1600;
  steppers[2].change_direction = false;
  steppers[3].dir_pin1 = 34;
  steppers[3].step_pin1 = 35;
  steppers[3].isDual = false;
  steppers[3].increment_step = 20;
  steppers[3].max_speed = 400;
  steppers[4].dir_pin1 = 32;
  steppers[4].step_pin1 = 33;
  //  steppers[4].dir_pin2 = 22;
  //  steppers[4].step_pin2 = 23;
  steppers[4].isDual = false;
  steppers[4].increment_step = 20;
  steppers[4].max_speed = 400;
  steppers[4].change_direction = false;
  steppers[5].dir_pin1 = 42;
  steppers[5].step_pin1 = 43;
  steppers[5].isDual = false;
  steppers[5].increment_step = 20;
  steppers[5].max_speed = 400;
  steppers[5].change_direction = false;

  steppers[0].stepper1 = new AccelStepper(1, steppers[0].step_pin1, steppers[0].dir_pin1);
  steppers[1].stepper1 = new AccelStepper(1, steppers[1].step_pin1, steppers[1].dir_pin1);
  //  steppers[1].stepper2 = new AccelStepper(1, steppers[1].step_pin2, steppers[1].dir_pin2);
  steppers[2].stepper1 = new AccelStepper(1, steppers[2].step_pin1, steppers[2].dir_pin1);
  //  steppers[2].stepper2 = new AccelStepper(1, steppers[2].step_pin2, steppers[2].dir_pin2);
  steppers[3].stepper1 = new AccelStepper(1, steppers[3].step_pin1, steppers[3].dir_pin1);
  steppers[4].stepper1 = new AccelStepper(1, steppers[4].step_pin1, steppers[4].dir_pin1);
   steppers[5].stepper1 = new AccelStepper(1, steppers[5].step_pin1, steppers[5].dir_pin1);
  //  steppers[4].stepper2 = new AccelStepper(1, steppers[4].step_pin2, steppers[4].dir_pin2);
  Serial.begin(115200); //define baud rate
  Serial.println("Testing Accelstepper"); //print a message
  pinMode(home_switch[0], INPUT_PULLUP);
  pinMode(home_switch[1], INPUT_PULLUP);
  pinMode(home_switch[2], INPUT_PULLUP);
  pinMode(home_switch[3], INPUT_PULLUP);
  pinMode(home_switch[4], INPUT_PULLUP);
  //setting up some default values for maximum speed and maximum acceleration
  setSpeedAndAcceleration();
  disableSteppers();
  // servo1.attach(6);

}
bool homeWasFind = false;

void loop()
{

  /////////////////////////// PS3 settings
#ifdef JOYSTICKACTIVATION
  if (threadCheckJoystick.shouldRun()) threadCheckJoystick.run();
#endif

  //Serial.println("BEYOND!");

  checkSerial(); //check serial port for new commands
  continuousRun2(); //method to handle the motor
  //   servo1.write(60);
  // delay(1000);
  // servo1.write(180);
  // delay(1000);
}

bool shouldSteppersGo()
{
  bool shouldSteppersGo = 0;
#ifdef DEBUG_REGIME
  if ( steppers[0].stepper1->distanceToGo() != 0)
  {
    Serial.print("shouldstepgo ZERO AXIS distance to go: \n");
    Serial.println(steppers[0].stepper1->distanceToGo());
  }
#endif
  for ( int i = 0; i < numberOfSteppers; i++)
  {
    //    if (steppers[i].stepper1->distanceToGo() > 20 || steppers[i].stepper1->distanceToGo() < -20)
    if (steppers[i].stepper1->distanceToGo() != 0)
    {
      shouldSteppersGo = 1;
      break;
    }
  }
  return shouldSteppersGo;
}

bool isEqualToReceivedPosition()
{
  bool isEqualToReceivedPosition = 1;
  for ( int i = 0; i < numberOfSteppers; i++)
  {
    if (steppers[i].stepper1->distanceToGo() != 0)
    {
      //  Serial.print("current position: " + String(steppers[i].stepper1->currentPosition()) + " Angle to reach: " + String(steppers[i].command1.angle) + " axis: " + String(i)  );
      isEqualToReceivedPosition = 0;
      break;
    }
  }
  return isEqualToReceivedPosition;
}


void continuousRun2() //method for the motor
{
  enableSteppers();
  while (shouldSteppersGo()) { // run untill condition
    if (mcpn_flag == true) {
      Serial.println("mcpn_flag is true, checking Serial port. ");
      checkSerial(); // check serial to check if i need to stop.
    }
    runSteppers();
#ifdef JOYSTICKACTIVATION
    if (isJoystickActivated == 1)
      if (threadCheckJoystick.shouldRun()) threadCheckJoystick.run();
#endif
  }
  //  if (shouldSteppersGo() == false)
  //    disableSteppers();
}

int pirateNumStep = 2;
bool isAllSwitchesAreActivated() {
  //numberOfSteppers
  for (int i = startHomingFrom; i < numberOfSteppers; i++)
  {
    if (i != 0 && i != 3 && i != 5) {
      if (!digitalRead(home_switch[i])) return false;
    } else if (digitalRead(home_switch[i])) return false;
  }
  Serial.println("all switches are activated.");

  return true;
}

void checkSerial() //method for receiving the commands
{
  String receivedCommand;
  if (Serial.available() > 0)
  {
    receivedCommand = Serial.readString();
    newData = true;
    Serial.print("RECEIVED MESSAGE: " + receivedCommand);
  }


  if (newData == true) //if we received something (see above)
  {


    //START - MEASURE
    if (receivedCommand.startsWith("mcp") || receivedCommand.startsWith("mcn")) //this is the measure part
    {
      int sign = 0;
      if (receivedCommand.startsWith("mcp")) {
        sign = 1;
      }
      else {
        sign = -1;
      }

      runallowed = true; //allow running
      int axis_number = receivedCommand.substring(3, 4).toInt() - 1;
      int received_speed = receivedCommand.substring(5, receivedCommand.length()).toInt();
      Serial.println("moving or stopping " + String(axis_number) + "axis in: + " + String(sign) + " direction. Speed: " + String(received_speed) );

      // stop forward or backward movement
      if ((mcpn_dir[axis_number] == 1 && sign == 1) || (mcpn_dir[axis_number] == -1 && sign == -1)) {
        if (steppers[axis_number].isDual)
        {
          steppers[axis_number].command1.angle  = steppers[axis_number].stepper1->currentPosition();// currentPosition of stepper1 to be synchro
          steppers[axis_number].command2.angle  = steppers[axis_number].stepper1->currentPosition();
          steppers[axis_number].stepper1->moveTo(steppers[axis_number].command1.angle);
          steppers[axis_number].stepper2->moveTo(steppers[axis_number].command2.angle);
        } else
        {
          steppers[axis_number].command1.angle = steppers[axis_number].stepper1->currentPosition();
          steppers[axis_number].stepper1->moveTo(steppers[axis_number].command1.angle);
          //  Serial.println("current position: " + String(steppers[axis_number].stepper1->currentPosition()) + " increment step is " + String(steppers[axis_number].increment_step) + " distance to go: " + String(steppers[axis_number].stepper1->distanceToGo()) + " angle: " + String(steppers[axis_number].command1.angle));
        }
        mcpn_dir[axis_number] = 0;
      } else // change direction
      {
        if (steppers[axis_number].isDual)
        {
          steppers[axis_number].command1.angle  =  100000 * sign;
          steppers[axis_number].command2.angle  =  100000 * sign;
          steppers[axis_number].command1.rotation_speed = received_speed;
          steppers[axis_number].command2.rotation_speed = received_speed;
          steppers[axis_number].stepper1->moveTo(steppers[axis_number].command1.angle);
          steppers[axis_number].stepper2->moveTo(steppers[axis_number].command2.angle);
          steppers[axis_number].stepper1->setMaxSpeed(steppers[axis_number].command1.rotation_speed);
          steppers[axis_number].stepper2->setMaxSpeed(steppers[axis_number].command2.rotation_speed);
        } else
        {
          steppers[axis_number].command1.angle = 100000 * sign;
          steppers[axis_number].command1.rotation_speed = received_speed;
          steppers[axis_number].stepper1->moveTo(steppers[axis_number].command1.angle);
          steppers[axis_number].stepper1->setMaxSpeed(steppers[axis_number].command1.rotation_speed);
          //  Serial.println("current position: " + String(steppers[axis_number].stepper1->currentPosition()) + " increment step is " + String(steppers[axis_number].increment_step) + " distance to go: " + String(steppers[axis_number].stepper1->distanceToGo()) + " angle: " + String(steppers[axis_number].command1.angle));
        }
        mcpn_dir[axis_number] = sign;
      }

      for (int i = 0; i < 5; i++)
      {
        if (mcpn_dir[i] != 0) {
          mcpn_flag = true; // here exist some movement in some direction
          break;
        }
        mcpn_flag = false;
      }
    }


    if (receivedCommand.startsWith("ap")) //this is the measure part
    {
      runallowed = true; //allow running
      int axis_number = receivedCommand.substring(2, 3).toInt() - 1;
      int steps_in_step = receivedCommand.substring(4, receivedCommand.length()).toInt();
      Serial.println("incremented axis: " + String(axis_number) + " with speed: " + String(steps_in_step));
      if (steppers[axis_number].isDual)
      {
        steppers[axis_number].command1.angle  +=  steps_in_step;
        steppers[axis_number].command2.angle  +=  steps_in_step;
        steppers[axis_number].command1.rotation_speed = steppers[axis_number].max_speed;
        steppers[axis_number].command2.rotation_speed = steppers[axis_number].max_speed;
      } else
      {
        steppers[axis_number].command1.angle += steps_in_step;
        steppers[axis_number].command1.rotation_speed = steppers[axis_number].max_speed;
        //  Serial.println("current position: " + String(steppers[axis_number].stepper1->currentPosition()) + " increment step is " + String(steppers[axis_number].increment_step) + " distance to go: " + String(steppers[axis_number].stepper1->distanceToGo()) + " angle: " + String(steppers[axis_number].command1.angle));
      }

      for (int i = 0; i < numberOfSteppers; i++) // asign move position
      {
        if (steppers[i].isDual)
        {
          steppers[i].stepper1->moveTo(steppers[i].command1.angle);
          steppers[i].stepper2->moveTo(steppers[i].command2.angle);
          steppers[i].stepper1->setMaxSpeed(steppers[i].max_speed);
          steppers[i].stepper2->setMaxSpeed(steppers[i].max_speed);
        } else
        {
          steppers[i].stepper1->moveTo(steppers[i].command1.angle);
          steppers[i].stepper1->setMaxSpeed(steppers[i].max_speed);
        }
      }
    }

    if (receivedCommand.startsWith("an")) //this is the measure part
    {
      runallowed = true; //allow running
      int axis_number = receivedCommand.substring(2, 3).toInt() - 1;
      int steps_in_step = receivedCommand.substring(4, receivedCommand.length()).toInt();
      Serial.println("decremented axis: " + String(axis_number) + " with speed: " + String(steps_in_step));
      if (steppers[axis_number].isDual)
      {
        steppers[axis_number].command1.angle -= steps_in_step;
        steppers[axis_number].command2.angle -= steps_in_step;
        steppers[axis_number].command1.rotation_speed = steppers[axis_number].max_speed;
        steppers[axis_number].command2.rotation_speed = steppers[axis_number].max_speed;
      } else
      {
        steppers[axis_number].command1.angle -= steps_in_step;
        steppers[axis_number].command1.rotation_speed = steppers[axis_number].max_speed;
        //  Serial.println("current position: " + String(steppers[axis_number].stepper1->currentPosition()) + " increment step is " + String(steppers[axis_number].increment_step) + " distance to go: " + String(steppers[axis_number].stepper1->distanceToGo()) + " angle: " + String(steppers[axis_number].command1.angle));
      }

      for (int i = 0; i < numberOfSteppers; i++) // asign move position
      {
        if (steppers[i].isDual)
        {
          steppers[i].stepper1->moveTo(steppers[i].command1.angle);
          steppers[i].stepper2->moveTo(steppers[i].command2.angle);
          steppers[i].stepper1->setMaxSpeed(steppers[i].max_speed);
          steppers[i].stepper2->setMaxSpeed(steppers[i].max_speed);
        } else
        {
          steppers[i].stepper1->moveTo(steppers[i].command1.angle);
          steppers[i].stepper1->setMaxSpeed(steppers[i].max_speed);
        }
        Serial.print(String(steppers[i].command1.angle) + " " + String(steppers[i].command1.rotation_speed) + " ");
      }
    }

    if (receivedCommand.startsWith("s")) //this is the measure part
    {

      command coms[commandsNum];
      parseValue(receivedCommand, ' ', coms);
      printReceivedCommands(coms);
      runallowed = true; //allow running

      // assign received angles and speed to each stepper
      for (int i = 0; i < commandsNum; i++)
      {
        if ( steppers[i].change_direction == true) {
          coms[i].angle = -coms[i].angle;

        }

        //        steppers[i].command1.rotation_speed = coms[i].rotation_speed;
        //        steppers[i].command2.rotation_speed = coms[i].rotation_speed;
      }
      for (int i = 0; i < numberOfSteppers; i++) // asign move position where to go
      {
        if (steppers[i].isDual)
        {
          steppers[i].stepper1->moveTo(coms[i].angle);
          steppers[i].stepper2->moveTo(coms[i].angle);
          steppers[i].stepper1->setMaxSpeed(coms[i].rotation_speed);
          steppers[i].stepper2->setMaxSpeed(coms[i].rotation_speed);
        } else
        {
          steppers[i].stepper1->moveTo(coms[i].angle);
          steppers[i].stepper1->setMaxSpeed(coms[i].rotation_speed);
        }
      }
    }

    //START - CLOSE
    if (receivedCommand.startsWith("c")) //CLOSING - Rotates the motor in the opposite direction as opening
    {
      //      //example c 2000 500 - 2000 steps (5 revolution with 400 step/rev microstepping) and 500 steps/s speed; will rotate in the other direction
      //      runallowed = true; //allow running
      //
      //
      //
      //      receivedMMdistance = Serial.parseFloat(); //value for the steps
      //      receivedDelay = Serial.parseFloat(); //value for the speed
      //
      //      Serial.print(receivedMMdistance);  //print the values for checking
      //      Serial.print(receivedDelay);
      //      Serial.println("CLOSE "); //print action
      //      stepper.setMaxSpeed(receivedDelay); //set speed
      //      stepper.moveTo(-1 * receivedMMdistance); ////set distance - negative value flips the direction

    }

    //STOP - STOP
    if (receivedCommand.startsWith("n")) //immediately stops the motor
    {
      //      runallowed = false; //disable running
      //
      //      stepper.setCurrentPosition(0); // reset position
      //      Serial.println("STOP "); //print action
      //      stepper.stop(); //stop motor
      //      stepper.disableOutputs(); //disable power

    }
    if (receivedCommand.startsWith("h")) //immediately stops the motor
    {
      int increment = 40;
      int incrementValue [numberOfSteppers] = {-increment, -increment, increment, -increment, -increment, -increment};

      runallowed = false; //disable running

      long initial_homing[numberOfSteppers] = {-1, -1, 1, -1, -1, -1};

      setDefaultParametersForSteppers();

      while (!isAllSwitchesAreActivated()) { // Make the Stepper move CCW until all switches are activated
        // 1 + cw - ccw [4000 -2000]    stoper = [ 1650 -3550.] homing ccw
        // 2 + cw - ccw [16000 -16000] stoper = [-22800 21200.] homing cw
        // 3 + cw - ccw [40000 -40000] stoper = [ -15700. 15700.] homing cw
        // 4 + cw - ccw [800 -800] stoper=[ -805 830.]  homing cw
        // 5 + cw - ccw [1200 -1200] stoper=[ -1800 1650.] homing cw
        Serial.println("HALLO1!. ");
        for (int i = startHomingFrom; i < numberOfSteppers; i++)
        {
          if (i != 0 && i != 3 && i != 5) // new buttons have reverse behavior, 0 axis button is an old one
          {
            if (!digitalRead(home_switch[i]))
            {
              {
                if ( steppers[i].change_direction == true) {
                  steppers[i].stepper1->moveTo(-initial_homing[i]);
                } else  steppers[i].stepper1->moveTo(initial_homing[i]);
                initial_homing[i] += incrementValue[i]; // add 1
                steppers[i].stepper1->run();
                }
            }
          }
          else
          {
            if (digitalRead(home_switch[i])) // if an old button
            {
              {
                if ( steppers[i].change_direction == true) {
                  steppers[i].stepper1->moveTo(-initial_homing[i]);
                } else  steppers[i].stepper1->moveTo(initial_homing[i]);
                initial_homing[i] += incrementValue[i]; // add 1
                steppers[i].stepper1->run();
                }
            }
          }
        }
      }

      Serial.println("Setting default parameters. 787 line. ");
      setDefaultParametersForSteppers();
      //      setDefaultParametersForSwitches();
      for (int i = 0; i < numberOfSteppers; i++) Serial.println("end " + String(i + 1) + " was reached. ");
      
      //go home
      for (int i = startHomingFrom; i < numberOfSteppers; i++)
      {
        {
          if ( steppers[i].change_direction == true) {
              steppers[i].stepper1->moveTo(-stepsToHome[i]);
          } else
          {
              steppers[i].stepper1->moveTo(stepsToHome[i]);
          }
        }
      }
      
      while (!isEqualToReceivedPosition())
      {
        runSteppers();
      }

      for (int i = 0; i < 5; i++) Serial.println("home " + String(i + 1) + " was reached. ");
      runallowed = false; //disable running
      setDefaultParametersForSteppers();
    }

    //    //SET DEFAULT PARAMETERS
    if (receivedCommand.startsWith("reset"))
    {
      setDefaultParametersForSteppers();
      Serial.println("Set default parameters."); //confirm update by message
    }

  }
  //after we went through the above tasks, newData becomes false again, so we are ready to receive new commands again.
  newData = false;


}