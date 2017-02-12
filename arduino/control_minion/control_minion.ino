int key;
//Arms Movements

#include <Servo.h>

Servo rightservo; 
Servo leftservo;// create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int blueeye = 5;
int redeye = 6;
int greeneye = 11;
int p,i,g,h;
int speakerOut = 3;


void setup() {
  Serial.begin(9600);

  rightservo.attach(8);  // attaches the servo on pin 9 to the servo object
  leftservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(11,OUTPUT);

  digitalWrite(blueeye,HIGH);
  digitalWrite(redeye,LOW);
  digitalWrite(greeneye,LOW);

  pinMode(speakerOut, OUTPUT);
  
}
  
void loop() {
  while (Serial.available()>0) {
    delay(10);
    key = Serial.read();

    Serial.print(key);

    switch(key){

    case '0': //confused arms
      
      digitalWrite(blueeye,HIGH);
      digitalWrite(redeye,LOW);
      digitalWrite(greeneye,LOW);
      rightservo.write(150);
      leftservo.write(0);
  
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
                                           // in steps of 1 degree
      leftservo.write( pos);
      rightservo.write(180- pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      }
    delay(500);
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      leftservo.write( pos);
      rightservo.write(180 -  pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
    }
  break;


  case '1'://left arm
    digitalWrite(redeye,LOW);
    digitalWrite(blueeye,LOW);
    digitalWrite(greeneye,HIGH);
    rightservo.write(150);
    leftservo.write(0);
  
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
                                          // in steps of 1 degree
      leftservo.write( pos);              // tell servo to go to position in variable 'pos'
      delay(7);                           // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      leftservo.write( pos);              // tell servo to go to position in variable 'pos'
      delay(7);                       // waits 15ms for the servo to reach the position
    }
  break;

  

  case '2'://right arm
    digitalWrite(redeye,LOW);
    digitalWrite(blueeye,LOW);
    digitalWrite(greeneye,HIGH);
    rightservo.write(150);
    leftservo.write(0);
  
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
                                          // in steps of 1 degree
      rightservo.write(180- pos);              // tell servo to go to position in variable 'pos'
      delay(7);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      rightservo.write(180 -  pos);              // tell servo to go to position in variable 'pos'
      delay(7);                       // waits 15ms for the servo to reach the position
    }
  break;

  case '3': //both arms
    digitalWrite(redeye,LOW);
    digitalWrite(blueeye,LOW);
    digitalWrite(greeneye,HIGH);
    rightservo.write(150);
    leftservo.write(0);
  
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
                                          // in steps of 1 degree
      leftservo.write( pos);
      rightservo.write(180- pos);              // tell servo to go to position in variable 'pos'
      delay(7);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      leftservo.write( pos);
      rightservo.write(180 -  pos);              // tell servo to go to position in variable 'pos'
      delay(7);                       // waits 15ms for the servo to reach the position
     }
   break;

  case '4': //wave
    digitalWrite(redeye,LOW);
    digitalWrite(blueeye,LOW);
    digitalWrite(greeneye,HIGH);
    rightservo.write(150);
    leftservo.write(0);
    
    p = 0;
    while(p<4){
      rightservo.write(150);
      for (pos = 110; pos <= 170; pos += 1) { // goes from 0 degrees to 180 degrees
                                              // in steps of 1 degree
        leftservo.write(pos);           
        delay(9);                     
      }
      p = p+1;
    }
  
    leftservo.write(300);
    break;
 
  case '5'://dancing
    digitalWrite(redeye,LOW);
    digitalWrite(blueeye,LOW);
    digitalWrite(greeneye,HIGH);
    rightservo.write(150);
    leftservo.write(0);
  
    i = 0;
    while(i<4){
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
                                            // in steps of 1 degree
        leftservo.write( pos);
        rightservo.write( pos);              // tell servo to go to position in variable 'pos'
        delay(4);                       // waits 15ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        leftservo.write( pos);
        rightservo.write(  pos);              // tell servo to go to position in variable 'pos'
        delay(4);                       // waits 15ms for the servo to reach the position
      }
      i = i +1;
    }
  break;

  case '6': //terminionator
    digitalWrite(greeneye,LOW);
    digitalWrite(blueeye,LOW);
    digitalWrite(redeye,HIGH);
    rightservo.write(150);
    leftservo.write(0);
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      leftservo.write( pos);
      rightservo.write(180- pos);              // tell servo to go to position in variable 'pos'
      delay(20);                       // waits 15ms for the servo to reach the position
    }

    int x = 1;
    while(x<5){
      tone(speakerOut,329);
      delay(600);
      tone(speakerOut,349);
      delay(600);
      x++;
    }

    while(x<12){
      tone(speakerOut,329);
      delay(300);
      tone(speakerOut,349);
      delay(300);
      x++;
    }
  
    tone(speakerOut,261);
    delay(1000);
    noTone(speakerOut);

    leftservo.write( 0);
    rightservo.write(150);
    digitalWrite(blueeye,HIGH);
    digitalWrite(redeye,LOW);
  break;  
  } // end of switch
  
  
  delay(10);
  }   
}
