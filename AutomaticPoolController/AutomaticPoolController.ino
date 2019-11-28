//==================================================================================
//Definitions
//==================================================================================

//General
#define ADC_MAX 1023
#define ADC_VCC 5                             //Volts

//State machine
#define STATE_IDLE 1
#defime STATE_LOW_RPM_PUMP 2
#define STATE_HIGH_RPM_PUMP 3

//getGHI function
#define SOLAR_CELL_ADC A5
#define SOLAR_CELL_ISC 6.00                   //Amps
#define CURRENT_SENSE_SENSITIVITY 2.5         //Amps per volt
#define CURRENT_SENSE_OFFSET 5*0.1            //Vcc*0.1
#define MAX_GHI 1000                          //Watts

//setPumpSpeed function
#define PUMP_SPEED_1 D2
#define PUMP_SPEED_2 D3
#define PUMP_SPEED_3 D4
#define PUMP_SPEED_4 D5


//==================================================================================
//Declarations
//==================================================================================

//State Machine
int intStateMachine = 1;


//==================================================================================
//Function: int getGHI()
//Description: returns the global horizonatal irradiance (watts)
//==================================================================================
int getGHI(){
  //Declarations
  float floADCVoltage = 0;
  float floSolarCurrent = 0;

  //Gets the ADC voltage
  floADCVoltage = (float)(ADC_VCC*((float)analogRead(SOLAR_CELL_ADC)/(float)ADC_MAX));

  //Gets the current
  floSolarCurrent = (float)((floADCVoltage - (float)URRENT_SENSE_OFFSET)*(float)CURRENT_SENSE_OFFSET);

  //Calculates and returns the total GHI
  return (int)(((float)floSolarCurrent/(float)SOLAR_CELL_ISC)*(float)MAX_GHI);
}

//==================================================================================
//Function: setPumpSpeed(int intPumpPreset)
//Description: sets the pump speed to a particular preset (use 0 to turn them all off)
//==================================================================================
void setPumpSpeed(int intPumpPreset){
  switch (intPumpPreset) {
    case 1:
      //Goes to speed preset 1
      digitalWrite(PUMP_SPEED_1,HIGH);
      digitalWrite(PUMP_SPEED_2,LOW);
      digitalWrite(PUMP_SPEED_3,LOW);
      digitalWrite(PUMP_SPEED_4,LOW);
      break;
    case 2:
      //Goes to speed preset 2
      digitalWrite(PUMP_SPEED_1,LOW);
      digitalWrite(PUMP_SPEED_2,HIGH);
      digitalWrite(PUMP_SPEED_3,LOW);
      digitalWrite(PUMP_SPEED_4,LOW);
      break;
    case 3:
      //Goes to speed preset 3
      digitalWrite(PUMP_SPEED_1,LOW);
      digitalWrite(PUMP_SPEED_2,LOW);
      digitalWrite(PUMP_SPEED_3,HIGH);
      digitalWrite(PUMP_SPEED_4,LOW);
      break;
    case 4:
      //Goes to speed preset 4
      digitalWrite(PUMP_SPEED_1,LOW);
      digitalWrite(PUMP_SPEED_2,LOW);
      digitalWrite(PUMP_SPEED_3,LOW);
      digitalWrite(PUMP_SPEED_4,HIGH);
      break;
   case 0:
      //Clears all presets
      digitalWrite(PUMP_SPEED_1,LOW);
      digitalWrite(PUMP_SPEED_2,LOW);
      digitalWrite(PUMP_SPEED_3,LOW);
      digitalWrite(PUMP_SPEED_4,LOW);
      break;
    default:
      //Clears all presets
      digitalWrite(PUMP_SPEED_1,LOW);
      digitalWrite(PUMP_SPEED_2,LOW);
      digitalWrite(PUMP_SPEED_3,LOW);
      digitalWrite(PUMP_SPEED_4,LOW);
      break;
  }
}



bool isSolarAvailable(){
  
}


int StateMachine(){
  //=====================
  //State: IDLE
  /======================
  if (intStateMachine == STATE_IDLE){
    //Do the stuff you need for idle state

    //Transition from IDLE
    if ((bolSweepTimerElapsed == false) && bolIsAfter7PM){
      //Transitions to PRIMING
      intStateMachine = STATE_HIGH_RPM_PUMP;
      break;
    }
    else if ((bolSolarAvailable) && (bolHeatingRequired)){
      //Transitions to PRIMING
      intStateMachine = STATE_HIGH_RPM_PUMP;
      break;
    }
  }
  
  if (intStateachine == STATE_HIGH_RPM_PUMP){
    if(bolTenMinuteTimerElapsed && bolHeatingRequired && bolTwoHourSweepDone && isSolarAvailable()){
      intStateMachine == STATE_LOW_RPM_PUMP;
      break;
    }
    else if(bolTenMinuteTimerElapsed && bolHeatingRequired && bolUserIterruptsSweep && isSolarAvailable()){
      intStateMachine == STATE_LOW_RPM_PUMP;
      break;
    }
  }

  if (intStateMachine == STATE_LOW_RPM_PUMP){
    if(bolHeatingDone)
      intStateMachine == IDLE
      break;
  }

}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  StateMachine();
  
}
