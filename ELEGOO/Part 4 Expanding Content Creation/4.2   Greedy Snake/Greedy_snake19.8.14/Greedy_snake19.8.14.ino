#include "LedControl.h"
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
// connection to MAX7219 (data, clik, load, #of dispplay)
LedControl lc = LedControl(13,7,8,1);
int16_t AcX,AcY;
// direction
int xVal = 0;
int yVal = 0;
const int UP    = 0;
const int RIGHT  = 1;
const int DOWN = 2;
const int LEFT   = 3;
// Snake length
const int MAX_SNAKE_LENGTH = 64;

// Variables
//Adafruit_8x8matrix matrix = Adafruit_8x8matrix();// Display
int direction = RIGHT;                             // direction of movement
int snakeX[MAX_SNAKE_LENGTH];                      // X-coordinates of snake
int snakeY[MAX_SNAKE_LENGTH];                      // Y-coordinates of snake
int snakeLength = 2;   
int score = 3;
unsigned long prevTime = 0;                        // for gamedelay (ms)
unsigned long delayTime = 500;                     // Game step in ms

int fruitX, fruitY;
unsigned long fruitPrevTime = 0;
unsigned long fruitBlinkTime = 100;

int fruitLed = true;



void setup(){
  ////wake up the MAX72XX from power-saving mode
  lc.shutdown(0,false);
  //set a medium brightness for the Leds
  lc.setIntensity(0, 1);
  //Switch all Leds on the display off.
  lc.clearDisplay(0);
  Serial.begin(9600);
  
  randomSeed(analogRead(A5));
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  
  
  snakeX[0] = 0;
  snakeY[0] = 4;
  for(int i=1; i<MAX_SNAKE_LENGTH; i++){
    snakeX[i] = snakeY[i] = -1;
  }
  makeFruit();
  
}
  
void loop(){
    delay(10);
    checkGy521();  // if any button is pressed or not
    unsigned long currentTime = millis();
    if(currentTime - prevTime >= delayTime){
    nextstep(); 
    prevTime = currentTime;
    int m=analogRead(A0);
    int n=analogRead(A1);
  }
  draw(); // make snack & food
  snakeItSelf(); // check if snack bite itself
}

void checkGy521(){
  static unsigned long delaytime = millis();
  if(millis() - delaytime > 20){
    delaytime = millis();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
    AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
    AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    delay(33);
    Serial.print(AcX);
    Serial.print('\t');  
    Serial.println(AcY); 
    if(AcX>-1600&&AcX<1600&&AcY>8000&&direction!= DOWN){
    direction=UP;
    Serial.println("DOWN");
    }
    else if(AcX>-1600&&AcX<1600&&AcY<-8000&& direction!= UP){
    direction=DOWN;
    Serial.println("UP");
    }
    else if(AcX<-8000&& AcY>-1600&&AcY<1600&& direction!= LEFT){
    direction=RIGHT;
    Serial.println("LEFT");
    }
    else if(AcX>8000&&AcY>-1600&&AcY<1600&& direction!= RIGHT){
    direction=LEFT;
    Serial.println("RIGHT");
    }
  }
}

void draw(){
  lc.clearDisplay(0);
  drawSnake();
  drawFruit();
}
void drawSnake(){
  for(int i=0; i<snakeLength; i++){
/* Set the status of a single Led.
 * Params :
 *   addr  address of the display
 *   row   the row of the Led (0..7)
 *   col   the column of the Led (0..7)
 *   state If true the led is switched on, if false it is switched off 

setLed(int addr, int row, int col, boolean state); 
*/ 
    lc.setLed(0,snakeX[i], snakeY[i], true);
  }
}
void drawFruit(){
  if(inPlayField(fruitX, fruitY)){
    unsigned long currenttime = millis();
    if(currenttime - fruitPrevTime >= fruitBlinkTime){
      /*
       *Fruit keeps flashing
      */
      fruitLed = (fruitLed == true) ? false : true;
      fruitPrevTime = currenttime;
    }
    lc.setLed(0,fruitX, fruitY, fruitLed);
  }
}
/*
 * Fruit appears range
*/
boolean inPlayField(int x, int y){
  return (x>=0) && (x<8) && (y>=0) && (y<8);
}


void nextstep(){
    for(int i=snakeLength-1; i>0; i--){
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1]; 
  }
    
  switch(direction){
    case UP:
      snakeY[0] = snakeY[0]-1; 
      if(snakeY[0]==-1)
      snakeY[0]=7;
      break;
    case RIGHT:
      snakeX[0] = snakeX[0]+1;
      if(snakeX[0]==8)
      snakeX[0]=0;
      break;
    case DOWN:
      snakeY[0] = snakeY[0]+1;
      if(snakeY[0]==8)
      snakeY[0]=0;
      break;
    case LEFT:
      snakeX[0]=snakeX[0]-1;
      if(snakeX[0]==-1)
      snakeX[0]=7;
      break;
   }

  if((snakeX[0] == fruitX) && (snakeY[0] == fruitY)){
    snakeLength++;
    score++;
    if(snakeLength < MAX_SNAKE_LENGTH){      
      makeFruit();
    } 
    else {
      fruitX = fruitY = -1;
    }
    if(score%8==0)
      {
        delayTime = delayTime - 50;
     }   
  }
   
}
/*
 * Fruit appears outside the snake body
*/
void makeFruit(){
  int x, y;
  x = random(0, 8);
  y = random(0, 8);
  while(isPartOfSnake(x, y)){
    x = random(0, 8);
    y = random(0, 8);
  }
  fruitX = x;
  fruitY = y;
}
/*
 * Determine where the fruit appears
*/
boolean isPartOfSnake(int x, int y){
  for(int i=0; i<snakeLength-1; i++){
    if((x == snakeX[i]) && (y == snakeY[i])){
      return true;
    }
  }
  return false;
}
/*
 * Snake head hits the snake body
*/
void snakeItSelf(){  // check if snake touches itself
    for(int i=1;i<snakeLength;i++){
      if((snakeX[0] == snakeX[i]) && (snakeY[0] == snakeY[i])){
       gameOver();
      }
     }
}
void gameOver(){
  lc.clearDisplay(0);
  for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            lc.setLed(0, r, c, HIGH);
            delay(50);
        }delay(50);
    }
  delay(300);
  score = 3;  
  snakeLength = 3;
  direction = RIGHT;
  snakeX[0]=3;
  snakeY[0]=4;
  delayTime = 500;
  loop();
}
