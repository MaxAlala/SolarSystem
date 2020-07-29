//If you found my video helpful, please SUBSCRIBE:  https://www.youtube.com/channel/UCKp1MzuAceJnDqAvsZl_46g
//The code belongs to the following tutorial video: https://youtu.be/AR0un3kg-iM
//example s 2000 4000 == 2000 steps (5 revolution with 400 step/rev microstepping) and 400 steps/s == 1 rev/sec speed

#include <AccelStepper.h>
#include <Servo.h>
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
const int current_step_multiplier[5] = {3,2,2,2,1};// where 1 is 8, 2 is 16, the logic is clear?
const int max_speed [5] = {1600, 3200, 3200, 1600, 800};
const long stepsToHome[5] = { -14200, -31000, 62000, -12400, -850}; // step == 1.8 / 4 
////////////////////////                    -29500
////////////////////////                    30000 to reach limit, 32000 to get back
bool isSwitchActivated[5] = { false, false, false, false, false}; // step == 1.8 / 4 



//steps per degree == 
// 1 axis == 8000/45 == 178 steps per 1 degree
// 2 axis == 22000/45 == 488 steps per 1 degree
// 3 axis == 31000/45 == 688 steps per 1 degree
// 4 axis == 6400/90 == 71 steps per 1 degree
// 5 axis == 500/45 = 11 steps per 1 degree
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
const int numberOfSteppers = 5;
const int commandsNum = numberOfSteppers;
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

const int home_switch[numberOfSteppers] = {22, 23, 24, 25, 26};

// s -1000 400 -1500 400 1500 400
// s -1000 500 2500 1000 6000 1000
// s 0 400 0 1000 0 1000


void setDefaultParametersForSwitches() {
  for (int i = 0; i < 5; i++)
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
      steppers[i].stepper1->setAcceleration(steppers[i].max_acc);
      steppers[i].stepper1->setMaxSpeed(steppers[i].max_speed);
      steppers[i].stepper2->setAcceleration(steppers[i].max_acc);
      steppers[i].stepper2->setMaxSpeed(steppers[i].max_speed);
    } else
    {
      steppers[i].stepper1->setAcceleration(steppers[i].max_acc);
      steppers[i].stepper1->setMaxSpeed(steppers[i].max_speed);
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
  int * separatorIndex = new int[10];
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

void setup()
{

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
  steppers[1].change_direction = true;
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

  
  steppers[0].stepper1 = new AccelStepper(1, steppers[0].step_pin1, steppers[0].dir_pin1);
  steppers[1].stepper1 = new AccelStepper(1, steppers[1].step_pin1, steppers[1].dir_pin1);
  //  steppers[1].stepper2 = new AccelStepper(1, steppers[1].step_pin2, steppers[1].dir_pin2);
  steppers[2].stepper1 = new AccelStepper(1, steppers[2].step_pin1, steppers[2].dir_pin1);
  //  steppers[2].stepper2 = new AccelStepper(1, steppers[2].step_pin2, steppers[2].dir_pin2);
  steppers[3].stepper1 = new AccelStepper(1, steppers[3].step_pin1, steppers[3].dir_pin1);
  steppers[4].stepper1 = new AccelStepper(1, steppers[4].step_pin1, steppers[4].dir_pin1);
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
  for ( int i = 0; i < numberOfSteppers; i++)
  {
    //    if (steppers[i].stepper1->distanceToGo() > 20 || steppers[i].stepper1->distanceToGo() < -20)
    if (steppers[i].stepper1->distanceToGo() != 0)
    {
      // Serial.print("current position: " + String(steppers[i].stepper1->currentPosition()) + " distance to go: " + String(steppers[i].stepper1->distanceToGo()) + " axis: " + String(i)  + "\n" );

      shouldSteppersGo = 1;
      break;
    }
    else { // finish your movement, WHY SHOULD STEpper gi to the current position??? If it is already hear
      if (steppers[i].isDual) {
        steppers[i].command1.angle = steppers[i].stepper1->currentPosition();
        steppers[i].command2.angle = steppers[i].stepper1->currentPosition();
        //        steppers[i].stepper1->moveTo(steppers[i].command1.angle);
        //        steppers[i].stepper2->moveTo(steppers[i].command2.angle);
      } else {
        steppers[i].command1.angle = steppers[i].stepper1->currentPosition();
        steppers[i].stepper1->moveTo(steppers[i].command1.angle);
      }
    }
  }
  return shouldSteppersGo;
}

bool isEqualToReceivedPosition()
{
  bool isEqualToReceivedPosition = 1;
  for ( int i = 0; i < numberOfSteppers; i++)
  {
    if (steppers[i].stepper1->currentPosition() != steppers[i].command1.angle)
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
  if (runallowed == true)
  {
    if (isEqualToReceivedPosition() == 0) { // check if we should enable steppers
      enableSteppers();
      while (shouldSteppersGo()) { // run untill condition
        if (mcpn_flag == true)checkSerial();
        runSteppers();
      }
    } else
    {
      runallowed = false;
      disableSteppers();
    }
  } else return;
}

int pirateNumStep = 2;
bool isAllSwitchesAreActivated() {
  //numberOfSteppers
  for (int i = 0; i < numberOfSteppers; i++)
  {
    if(i != 0) {
      if (!digitalRead(home_switch[i])) return false; 
    }else if (digitalRead(home_switch[i])) return false;
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

    //////get data from esp3266 == short command
    //    String controlMsgStile = "AXIS";
    //    if (receivedCommand.substring(0, 4).equals(controlMsgStile)) {
    //      Serial.print("COMMAND was received: " + receivedCommand);
    //      command com = getValues(receivedCommand, ' ');
    //      Serial.println("Parsed commands: " + String(com.axis) + " " + String(com.angle));
    //      //Serial.println(com.axis.toInt());
    //      int speed1 = 400;
    //      int speed2 = 1600;
    //      int speed3 = 1600;
    //      int speed4 = 400;
    //      int speed5 = 400;

    //      switch (com.axis)
    //      {
    //        case 1:
    //          Serial.println("hello1 ");
    //          receivedMMdistance = com.angle; //value for the steps
    //          receivedDelay = speed1; //value for the speed
    //          Serial.println(receivedMMdistance);
    //          stepper.setMaxSpeed(receivedDelay); //set speed
    //          stepper.moveTo(receivedMMdistance); //set distance
    //          break;
    //        case 2:
    //          Serial.println("hello2 ");
    //          receivedMMdistance2 = com.angle; //value for the steps
    //          receivedDelay2 = speed2; //value for the speed
    //          receivedMMdistance2_1 = receivedMMdistance2; //value for the steps
    //          receivedDelay2_1 = receivedDelay2; //value for the speed
    //          stepper2.setMaxSpeed(receivedDelay2); //set speed
    //          stepper2.moveTo(receivedMMdistance2); //set distance
    //          stepper2_1.setMaxSpeed(receivedDelay2_1); //set speed
    //          stepper2_1.moveTo(receivedMMdistance2_1); //set distance
    //          break;
    //        case 3:
    //          receivedMMdistance3_1 = com.angle; //value for the steps
    //          receivedDelay3_1 = speed3; //value for the speed
    //          receivedMMdistance3 = -receivedMMdistance3_1; //value for the steps
    //          receivedDelay3 = receivedDelay3_1; //value for the speed
    //          stepper3.setMaxSpeed(receivedDelay3); //set speed
    //          stepper3.moveTo(receivedMMdistance3); //set distance
    //          stepper3_1.setMaxSpeed(receivedDelay3_1); //set speed
    //          stepper3_1.moveTo(receivedMMdistance3_1); //set distance
    //          break;
    //        case 4:
    //          receivedMMdistance4 = com.angle; //value for the steps
    //          receivedDelay4 = speed4; //value for the speed
    //          stepper4.setMaxSpeed(receivedDelay4); //set speed
    //          stepper4.moveTo(receivedMMdistance4); //set distance
    //          break;
    //        case 5:
    //          receivedMMdistance5 = com.angle; //value for the steps
    //          receivedDelay5 = speed5; //value for the speed
    //          stepper5.setMaxSpeed(receivedDelay5); //set speed
    //          stepper5.moveTo(receivedMMdistance5); //set distance
    //          break;
    //        case 6:
    //          break;
    //      }
    //
    //    }
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
        if ( steppers[i].change_direction == true){
          steppers[i].command1.angle = -coms[i].angle;
          steppers[i].command2.angle = -coms[i].angle;
        }else
        {
          steppers[i].command1.angle = coms[i].angle;
          steppers[i].command2.angle = coms[i].angle;
        }
        
        steppers[i].command1.rotation_speed = coms[i].rotation_speed;
        steppers[i].command2.rotation_speed = coms[i].rotation_speed;
        Serial.print(String(steppers[i].command1.angle) + " " + String(steppers[i].command1.rotation_speed) + " ");
      }
      for (int i = 0; i < numberOfSteppers; i++) // asign move position where to go
      {
        if (steppers[i].isDual)
        {
          steppers[i].stepper1->moveTo(steppers[i].command1.angle);
          steppers[i].stepper2->moveTo(steppers[i].command2.angle);
          steppers[i].stepper1->setMaxSpeed(steppers[i].command1.rotation_speed);
          steppers[i].stepper2->setMaxSpeed(steppers[i].command2.rotation_speed);
        } else
        {
          steppers[i].stepper1->moveTo(steppers[i].command1.angle);
          steppers[i].stepper1->setMaxSpeed(steppers[i].command1.rotation_speed);
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
      int increment = 80;
      int incrementValue [5] = {increment, increment, -increment, increment, increment};

      runallowed = false; //disable running

      long initial_homing[5] = {1, 1, -1, 1, 1};

      setDefaultParametersForSteppers();

      while (!isAllSwitchesAreActivated()) { // Make the Stepper move CCW until all switches are activated
        // 1 + cw - ccw [4000 -2000]    stoper = [ 1650 -3550.] homing ccw
        // 2 + cw - ccw [16000 -16000] stoper = [-22800 21200.] homing cw
        // 3 + cw - ccw [40000 -40000] stoper = [ -15700. 15700.] homing cw
        // 4 + cw - ccw [800 -800] stoper=[ -805 830.]  homing cw
        // 5 + cw - ccw [1200 -1200] stoper=[ -1800 1650.] homing cw
        Serial.println("HALLO1!. ");
        for (int i = 0; i < numberOfSteppers; i++)
        {
          if (i != 0) // new buttons have reverse behavior, 0 button is an old one
          {

//            if(!digitalRead(home_switch[i]))
//            isSwitchActivated[i] = true;
            if (!digitalRead(home_switch[i]))
            {
              if (steppers[i].isDual)
              {
                steppers[i].stepper1->moveTo(initial_homing[i]);
                steppers[i].stepper2->moveTo(initial_homing[i]);
                initial_homing[i] += incrementValue[i]; // add 1
                steppers[i].stepper1->run();
                steppers[i].stepper2->run();
                //            Serial.println("move to: " + String(initial_homing[i]) + ". increment value: " + String(incrementValue[i]));
              } else
              {
                if ( steppers[i].change_direction == true){
                  steppers[i].stepper1->moveTo(-initial_homing[i]);
                }else  steppers[i].stepper1->moveTo(initial_homing[i]);
                initial_homing[i] += incrementValue[i]; // add 1
                steppers[i].stepper1->run();
                //              Serial.println("move to: " + String(initial_homing[i]) + ". increment value: " + String(incrementValue[i]));
              }
            }
          }
          else 
          {
//                      if(digitalRead(home_switch[i]))
//            isSwitchActivated[i] = true;
//           
          if (digitalRead(home_switch[i])) // if an old button
          {
            if (steppers[i].isDual)
            {
              steppers[i].stepper1->moveTo(initial_homing[i]);
              steppers[i].stepper2->moveTo(initial_homing[i]);
              initial_homing[i] += incrementValue[i]; // add 1
              steppers[i].stepper1->run();
              steppers[i].stepper2->run();
              //                Serial.println("move to: " + String(initial_homing[i]) + ". increment value: " + String(incrementValue[i]));
            } else
            {
              if ( steppers[i].change_direction == true){
                  steppers[i].stepper1->moveTo(-initial_homing[i]);
              }else  steppers[i].stepper1->moveTo(initial_homing[i]);
              initial_homing[i] += incrementValue[i]; // add 1
              steppers[i].stepper1->run();
              //              Serial.println("move to: " + String(initial_homing[i]) + ". increment value: " + String(incrementValue[i]));
            }
          }
          }
        }
      }
      Serial.println("Setting default parameters. 787 line. ");
      setDefaultParametersForSteppers();
//      setDefaultParametersForSwitches();
      for (int i = 0; i < 5; i++) Serial.println("end " + String(i + 1) + " was reached. ");

      // 1 + cw - ccw [4000 -2000]   stoper = [ 1650 -3550.] homing ccw
      // 2 + cw - ccw [16000 -16000] stoper = [-22800 21200.] homing cw
      // 3 + cw - ccw [40000 -40000] stoper = [ -15700. 15700.] homing cw
      // 4 + cw - ccw [800 -800]     stoper=[ -805 830.]  homing cw
      // 5 + cw - ccw [1200 -1200]   stoper=[ -1800 1650.] homing cw
      //      stepper.moveTo(-2025); //ccw
      //      stepper2.moveTo(-21200); //ccw
      //      stepper2_1.moveTo(-21200); // cww
      //      stepper3_1.moveTo(13800); // cw
      //      stepper3.moveTo(-13800); // cw
      //      stepper4.moveTo(-770); // cww
      //      stepper5.moveTo(-1650); // cww
      //go home
      for (int i = 0; i < numberOfSteppers; i++)
      {
        if (steppers[i].isDual)
        {
          steppers[i].command1.angle = stepsToHome[i];
          steppers[i].command2.angle = stepsToHome[i];
          steppers[i].stepper1->moveTo(steppers[i].command1.angle);
          steppers[i].stepper2->moveTo(steppers[i].command2.angle);
        } else
        {
          if ( steppers[i].change_direction == true){
            steppers[i].command1.angle = -stepsToHome[i];
          }else
          { 
          steppers[i].command1.angle = stepsToHome[i];
          }
          steppers[i].stepper1->moveTo(steppers[i].command1.angle);
        }
      }
      runallowed = true; //disable running
      while (!isEqualToReceivedPosition())
      {
        runSteppers();
      }

      for (int i = 0; i < 5; i++) Serial.println("home " + String(i + 1) + " was reached. ");
      runallowed = false; //disable running
      setDefaultParametersForSteppers();
    }

    //    //SET ACCELERATION
        if (receivedCommand.startsWith("reset")) //Setting up a new acceleration value
        {
          runallowed = false; //we still keep running disabled, since we just update a variable
          setDefaultParametersForSteppers();
          receivedAcceleration = Serial.parseFloat(); //receive the acceleration from serial
          Serial.println("Set default parameters."); //confirm update by message   
        }

  }
  //after we went through the above tasks, newData becomes false again, so we are ready to receive new commands again.
  newData = false;


}
