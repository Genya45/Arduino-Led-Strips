#include "NewTone.h"

#include "IRremote.h"
IRrecv irrecv(2); 
decode_results results;

//#define BUp 551486205
//#define BDown 551518845
//#define BRemote 551490795
//#define BRed 551505585
//#define BGreen 551521905
//#define BYellow 551536185
//#define BBlue 551519865
//#define BOk 551494365
//#define BLeft 551542815
//#define BRight 551510175
//#define BNull 4294967295
//
//#define B1 551520375
//#define B2 551504055
//#define B3 551536695
//#define B4 551495895
//#define B5 551528535
//#define B6 551512215
//#define B7 551544855
//#define B8 551491815
//#define B9 551524455
//#define B0 551487735
//#define BMute 551522415
//#define BSong 551528790

#define BUp 33738799
#define BDown 33714319
#define BRemote 33732679
#define BRed 33736759
#define BGreen 33740839
#define BYellow 33695959
#define BBlue 33694429
#define BOk 33730639
#define BLeft 33687799
#define BRight 33720439
#define BNull 4294967295

#define B1 33718399
#define B2 33702079
#define B3 33734719
#define B4 33693919
#define B5 33726559
#define B6 33710239
#define B7 33742879
#define B8 33689839
#define B9 33722479
#define B0 33685759
#define BMute 33746959
#define BSong 33697999

int redPin = 10;
int greenPin = 9;
int bluePin = 6;
int tonePin = 5;

int currentR = 0;

//begushaya_lenta
int begushaya_lenta_timer = 200;
unsigned long bg_l_first_time = 0;
bool ifRight = true;

//posledovatelnost
int PRed = 0;
int PGreen = 0;
int PBlue = 0;
int PCurCol = 0;
unsigned long PTime = 0;


//newRandom
int currentRed = random(255);
int currentBlue = random(255);
int currentGreen =  random(255);
int prevRed = 0;
int prevBlue = 0;
int prevGreen = 0;
double  prevTime = 0;
double nextTime = 0;



int colorRed = 255;
int colorGreen = 255;
int colorBlue = 255;
int currentColor = 1;

bool isSetColor = false;


//tone


int frequences[] = {
293, 493, 440, 391, 293, 293, 293, 493, 440, 391, 
329, 329, 329, 523, 493, 440, 587, 587, 659, 587, 
523, 440, 493, 293, 293, 493, 440, 391, 293, 293, 
293, 493, 440, 391, 329, 329, 329, 523, 493, 440, 
587, 587, 587, 587, 659, 587, 523, 440, 391, 587, 
493, 493, 493, 493, 493, 493, 493, 587, 391, 440, 
493, 523, 523, 523, 523, 523, 493, 493, 493, 493, 
493, 440, 440, 493, 440, 587, 493, 493, 493, 493, 
493, 493, 493, 587, 391, 440, 493, 523, 523, 523, 
523, 523, 493, 493, 493, 493, 587, 587, 523, 440, 
391 
};
int durations[] = {
250, 250, 250, 250, 750, 250, 250, 250, 250, 250, 
750, 250, 250, 250, 250, 250, 750, 250, 250, 250, 
250, 250, 750, 250, 250, 250, 250, 250, 750, 250, 
250, 250, 250, 250, 750, 250, 250, 250, 250, 250, 
250, 250, 250, 250, 250, 250, 250, 250, 500, 500, 
250, 250, 500, 250, 250, 500, 250, 250, 375, 125, 
1000, 250, 250, 375, 125, 250, 250, 250, 125, 125, 
250, 250, 250, 250, 500, 500, 250, 250, 500, 250, 
250, 500, 250, 250, 375, 125, 1000, 250, 250, 375, 
125, 250, 250, 250, 125, 125, 250, 250, 250, 250, 
750, 
};
int countNote = 101;
unsigned long TimeMusic = 0;
int currentNote = 0;
bool ifListenMusic = false;
bool ifMute = false;



unsigned long beforeButton = 0;
void setup()

{
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
 // pinMode(tonePin,OUTPUT);

  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);

  pinMode(A0, INPUT);

  irrecv.enableIRIn(); 
}


void loop()

{



//      if(millis()%5000 == 0){
//        begushaya_lenta_timer = random(200) + 55 ;
//        if(ifRight) ifRight = false;
//        else ifRight = true;
//        if(ifRight)Serial.println(1);
//        else Serial.println(2);
//      }
  // begushaya_lenta_timer = analogWrite(A0);

//  midi();

  if ( irrecv.decode( &results )) { 
    irrecv.resume(); // принимаем следующую команду
    //Serial.println(results.value);

    if(results.value == B9){
      isSetColor = !isSetColor;
      
      if(isSetColor == true)Serial.println(1);
      else Serial.println(2);
    }

    if(results.value!=BNull && ifMute==false){
      NewTone(tonePin,2000,30);
    }
    else if(results.value==BNull && ifMute==false)
      NewTone(tonePin,500,10);
    
    switch(results.value){
      case BUp:{
        currentR++;
        if(currentR == 9)currentR = 1;
        break;
      }
      case BDown:{
        currentR--;
        if(currentR <1)currentR = 8;
        
        break;
      }
      case BRemote:{
        if(ifRight) ifRight = false;
        else ifRight = true;
        break;
      }
      case BRed:{
          currentR = 8;
          colorRed = 255;
          colorGreen = 0;
          colorBlue = 0;
        break;
      }      
      case BGreen:{
          currentR = 8;
          colorRed = 0;
          colorGreen = 255;
          colorBlue = 0;
        break;
      }            
      case BYellow:{
          currentR = 8;
          colorRed = 255;
          colorGreen = 255;
          colorBlue = 255;
        break;
      }
      case BBlue:{
          currentR = 8;
          colorRed = 0;
          colorGreen = 0;
          colorBlue = 255;
        break;
      }
      case BLeft:{
        if(currentR == 8 || isSetColor == true){
            switch(currentColor){
              case 1:{
              if(colorRed>=5) colorRed -=5;
              break;}
              case 2:{
              if(colorGreen>=5) colorGreen -=5;  
              break;}            
              case 3:{
              if(colorBlue>=5) colorBlue -=5;  
              break;}
            }
            break;
        }
        
        if(beforeButton == BLeft && begushaya_lenta_timer>10)
        begushaya_lenta_timer-=10;
        
        break;
      }
      case BRight:{
        if(currentR == 8 || isSetColor == true){
            switch(currentColor){
              case 1:{
              if(colorRed<=250) colorRed +=5;
              break;}
              case 2:{
              if(colorGreen<=250) colorGreen +=5;  
              break;}            
              case 3:{
              if(colorBlue<=250) colorBlue +=5;  
              break;}
              }
            break;
        }
        
        if(beforeButton == BRight && begushaya_lenta_timer<=1000)
        begushaya_lenta_timer+=10;
        break;
      }  
      case BNull:{
        if(beforeButton == BLeft && begushaya_lenta_timer>50 && isSetColor == false)
        begushaya_lenta_timer-=10;
        if(beforeButton == BRight && begushaya_lenta_timer<=1000 && isSetColor == false)
        begushaya_lenta_timer+=10;
        if(currentR == 8 || isSetColor == true){
          
          if(beforeButton == BLeft){
            switch(currentColor){
              case 1:{
              if(colorRed>=10) colorRed -=10;
              break;}
              case 2:{
              if(colorGreen>=10) colorGreen -=10;  
              break;}            
              case 3:{
              if(colorBlue>=10) colorBlue -=10;  
              break;}
            }
          }
          if(beforeButton == BRight){
            switch(currentColor){
              case 1:{
              if(colorRed<=245) colorRed +=10;
              break;}
              case 2:{
              if(colorGreen<=245) colorGreen +=10;  
              break;}            
              case 3:{
              if(colorBlue<=245) colorBlue +=10;  
              break;}
            }
          }


          
        }
        break;
      }  
      case BOk:{
        currentColor++;
        if(currentColor==4)currentColor = 1;
        break;

      }
      case B1:{
        currentR = 1;
        break;
      } 
      case B2:{
        currentR = 2;
        break;
      } 
      case B3:{
        currentR = 3;
        break;
      } 
      case B4:{
        currentR = 4;
        break;
      } 
      case B5:{
        currentR = 5;
        break;
      } 
      case B6:{
        currentR = 6;
        break;
      } 
      case B7:{
        currentR = 7;
        break;
      } 
      case B8:{
        currentR = 8;
        break;
      } 
      case B0:{
        currentR = 0;
        break;
      } 
      case BMute:{
        ifMute =!ifMute;
        break;
      }      
      case BSong:{
        ifListenMusic = !ifListenMusic;
        currentNote = 0;
        if(ifListenMusic == true)TimeMusic = millis();
      }



           
    }
    if(results.value!= BNull)beforeButton = results.value;
  }

  switch(currentR){
    case 0:
      setColor(0,0,0);  
      break;
    case 1:
      begushaya_lenta1();  
      break;
    case 2:
      begushaya_lenta2();  
      break;
    case 3:
      begushaya_lenta3();  
      break;
    case 4:
      begushaya_lenta4();  
      break;
    case 5:
      posledovatelnost();  
      break;
    case 6:
      newRandom(); 
      break;
    case 7:
      police();
      break;
    case 8:
      setColor(colorRed,colorGreen,colorBlue);
      break;   
  }




//  begushaya_lenta1();  
//  begushaya_lenta2(); 
//  begushaya_lenta3(); 
//  begushaya_lenta4(); 

//posledovatelnost();
 //  newRandom();
//  setColor(255,0,0);
//  setColor(0,255,0);
//  setColor(0,0,255);
//  setColor(0,255,255);


if(ifListenMusic==true)music();

}

void setColor(int red, int green, int blue)

{

  red = 255 - red;

  green = 255 - green;

  blue = 255 - blue;

  analogWrite(redPin, red);

  analogWrite(greenPin, green);

  analogWrite(bluePin, blue);

}






































































  void begushaya_lenta1(){
    if(millis()<bg_l_first_time+begushaya_lenta_timer)
      setColor(colorRed, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer && millis()<bg_l_first_time+begushaya_lenta_timer*2){
      if(ifRight)
        setColor(0, colorGreen, 0);
      else
        setColor(0, 0, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*2 && millis()<bg_l_first_time+begushaya_lenta_timer*3){
      if(ifRight)
        setColor(0, 0, colorBlue);
      else
        setColor(0, colorGreen, 0);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*3)
      bg_l_first_time = millis();
  }



  void begushaya_lenta2(){
    if(millis()<bg_l_first_time+begushaya_lenta_timer)
      setColor(colorRed, colorRed, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer && millis()<bg_l_first_time+begushaya_lenta_timer*2){
      if(ifRight)
        setColor(0, colorGreen, colorBlue);
      else
        setColor(colorRed, 0, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*2 && millis()<bg_l_first_time+begushaya_lenta_timer*3){
      if(ifRight)
        setColor(colorRed, 0, colorBlue);
      else
        setColor(0, colorGreen, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*3)
      bg_l_first_time = millis();
  }





  void begushaya_lenta3(){
    if(millis()<bg_l_first_time+begushaya_lenta_timer)
      setColor(colorRed, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer && millis()<bg_l_first_time+begushaya_lenta_timer*1.5)
      setColor(0, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*1.5 && millis()<bg_l_first_time+begushaya_lenta_timer*2.5)
      setColor(colorRed, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*2.5 && millis()<bg_l_first_time+begushaya_lenta_timer*3.5)
      setColor(0, 0, 0);

    if(millis()>bg_l_first_time+begushaya_lenta_timer*3.5 && millis()<bg_l_first_time+begushaya_lenta_timer*4.5){
      if(ifRight)
        setColor(0, colorGreen, 0);
      else
        setColor(0, 0, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*4.5 && millis()<bg_l_first_time+begushaya_lenta_timer*5)
      setColor(0, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*5 && millis()<bg_l_first_time+begushaya_lenta_timer*6){
      if(ifRight)
        setColor(0, colorGreen, 0);
      else
        setColor(0, 0, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*6 && millis()<bg_l_first_time+begushaya_lenta_timer*7)
      setColor(0, 0, 0);

    if(millis()>bg_l_first_time+begushaya_lenta_timer*7 && millis()<bg_l_first_time+begushaya_lenta_timer*8){
      if(ifRight)
        setColor(0, 0, colorBlue);
      else
        setColor(0, colorGreen, 0);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*8 && millis()<bg_l_first_time+begushaya_lenta_timer*8.5)
      setColor(0, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*8.5 && millis()<bg_l_first_time+begushaya_lenta_timer*9.5){
      if(ifRight)
        setColor(0, 0, colorBlue);
      else
        setColor(0, colorGreen, 0);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*9.5 && millis()<bg_l_first_time+begushaya_lenta_timer*10.5)
      setColor(0, 0, 0);
     
      
    if(millis()>bg_l_first_time+begushaya_lenta_timer*10.5)
      bg_l_first_time = millis();
  }

 




  

  void begushaya_lenta4(){
    if(millis()<bg_l_first_time+begushaya_lenta_timer)
      setColor(colorRed, colorGreen, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer && millis()<bg_l_first_time+begushaya_lenta_timer*1.5)
      setColor(0, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*1.5 && millis()<bg_l_first_time+begushaya_lenta_timer*2.5)
      setColor(colorRed, colorGreen, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*2.5 && millis()<bg_l_first_time+begushaya_lenta_timer*3.5)
      setColor(0, 0, 0);

    if(millis()>bg_l_first_time+begushaya_lenta_timer*3.5 && millis()<bg_l_first_time+begushaya_lenta_timer*4.5){
      if(ifRight)
        setColor(0, colorGreen, colorBlue);
      else
        setColor(colorRed, 0, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*4.5 && millis()<bg_l_first_time+begushaya_lenta_timer*5)
      setColor(0, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*5 && millis()<bg_l_first_time+begushaya_lenta_timer*6){
      if(ifRight)
        setColor(0, colorGreen, colorBlue);
      else
        setColor(colorRed, 0, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*6 && millis()<bg_l_first_time+begushaya_lenta_timer*7)
      setColor(0, 0, 0);

    if(millis()>bg_l_first_time+begushaya_lenta_timer*7 && millis()<bg_l_first_time+begushaya_lenta_timer*8){
      if(ifRight)
        setColor(colorRed, 0, colorBlue);
      else
        setColor(0, colorGreen, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*8 && millis()<bg_l_first_time+begushaya_lenta_timer*8.5)
      setColor(0, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*8.5 && millis()<bg_l_first_time+begushaya_lenta_timer*9.5){
      if(ifRight)
        setColor(colorRed, 0, colorBlue);
      else
        setColor(0, colorGreen, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*9.5 && millis()<bg_l_first_time+begushaya_lenta_timer*10.5)
      setColor(0, 0, 0);
     
      
    if(millis()>bg_l_first_time+begushaya_lenta_timer*10.5)
      bg_l_first_time = millis();
  }



  void posledovatelnost(){
    if(bg_l_first_time<millis()){
      bg_l_first_time = millis() + begushaya_lenta_timer/100;
      switch(PCurCol){
        case 0:
          PRed++;
          if(PRed == 255)
            PCurCol++;
          break;
        case 1:
          PRed--;
          if(PRed<40)
            PGreen++;
          if(PRed == 0)
            PCurCol++;
          break;
        case 2:
          PGreen++;
          if(PGreen == 255)
            PCurCol++;
          break;
        case 3:
          PGreen--;
          if(PGreen<40)
            PBlue++;
          if(PGreen == 0)
            PCurCol++;
          break;
        case 4:
          PBlue++;
          if(PBlue == 255)
            PCurCol++;
          break;
        case 5:
          PBlue--;
          if(PBlue<40)
            PRed++;
          if(PBlue == 0)
            PCurCol++;
          break;
        default:
          PCurCol = 0;
          break;
      }
    }
    setColor(PRed, PGreen, PBlue);
  }



void newRandom(){
  if(millis() > nextTime){

    nextTime = nextTime + begushaya_lenta_timer/20;
    
    if(currentRed == prevRed){
      prevRed = random(255);
    }
    if(currentRed > prevRed){
      currentRed--;
    }
    if(currentRed < prevRed){
      currentRed++;
    }
    if(currentBlue == prevBlue){
      prevBlue = random(255);
    }
    if(currentBlue > prevBlue){
      currentBlue--;
    }
    if(currentBlue < prevBlue){
      currentBlue++;
    }
    if(currentGreen == prevGreen){
      prevGreen = random(255);
    }
    if(currentGreen > prevGreen){
      currentGreen--;
    }
    if(currentGreen < prevGreen){
      currentGreen++;
    }
    setColor(currentRed,currentBlue,currentGreen);
  }
}

void police(){
    if(millis()<bg_l_first_time+begushaya_lenta_timer)
      setColor(colorRed, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer && millis()<bg_l_first_time+begushaya_lenta_timer*1.5)
      setColor(0, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*1.5 && millis()<bg_l_first_time+begushaya_lenta_timer*2.5)
      setColor(colorRed, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*2.5 && millis()<bg_l_first_time+begushaya_lenta_timer*3.5)
      setColor(0, 0, 0);


    if(millis()>bg_l_first_time+begushaya_lenta_timer*7 && millis()<bg_l_first_time+begushaya_lenta_timer*8){
      setColor(0, 0, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*8 && millis()<bg_l_first_time+begushaya_lenta_timer*8.5)
      setColor(0, 0, 0);
    if(millis()>bg_l_first_time+begushaya_lenta_timer*8.5 && millis()<bg_l_first_time+begushaya_lenta_timer*9.5){
      setColor(0, 0, colorBlue);
    }
    if(millis()>bg_l_first_time+begushaya_lenta_timer*9.5 && millis()<bg_l_first_time+begushaya_lenta_timer*10.5)
      setColor(0, 0, 0);
     
      
    if(millis()>bg_l_first_time+begushaya_lenta_timer*10.5)
      bg_l_first_time = millis();
  }






void music(){
  int frequence = frequences[currentNote];
  int duration = 0;
  int noDuration = 0;

   if(durations[currentNote]==250){
    duration = (durations[currentNote]-25);
    noDuration = 25;
   }
   else if(durations[currentNote]==750){
    duration = (durations[currentNote]-300);
    noDuration = 300;
   }
   else if(durations[currentNote]==125){
    duration = (durations[currentNote]-13);
    noDuration = 13;
   }
   else {
    duration = (durations[currentNote]);
    noDuration = 25;
   }

   if(millis()< TimeMusic + duration)
    NewTone(tonePin,frequences[currentNote]);
   else if(millis()< TimeMusic + duration + noDuration )
    noNewTone(tonePin);
   else{
    TimeMusic = millis();
    currentNote++;
    if(currentNote>100)currentNote=0;
   }
  
}




//
//// Jingle Bells
//
//void midi() {
//	
//	if(millis()<toneTime + 250)
//		NewTone(tonePin, 293, 225.0);
//    else if (millis()<toneTime + 500)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 750)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 1000)
//		NewTone(tonePin, 391, 225.0);
//	else if (millis()<toneTime + 1750)
//		NewTone(tonePin, 293, 450.0);
//	else if (millis()<toneTime + 2000)
//		NewTone(tonePin, 293, 225.0);
//	else if (millis()<toneTime + 2250)
//		NewTone(tonePin, 293, 225.0);
//	else if (millis()<toneTime + 2500)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 2750)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 3000)
//		NewTone(tonePin, 391, 225.0);
//	else if (millis()<toneTime + 3750)
//		NewTone(tonePin, 329, 450.0);
//	else if (millis()<toneTime + 4500)
//		NewTone(tonePin, 329, 225.0);
//	else if (millis()<toneTime + 4750)
//		NewTone(tonePin, 329, 225.0);
//	else if (millis()<toneTime + 5000)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 5250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 5500)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 5750)
//		NewTone(tonePin, 587, 450.0);
//	else if (millis()<toneTime + 6500)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 6750)
//		NewTone(tonePin, 659, 225.0);
//	else if (millis()<toneTime + 7000)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 7250)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 7500)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 7750)
//		NewTone(tonePin, 493, 675.0);
//	else if (millis()<toneTime + 8500)
//		NewTone(tonePin, 293, 225.0);
//	else if (millis()<toneTime + 9000)
//		NewTone(tonePin, 293, 225.0);
//	else if (millis()<toneTime + 9250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 9500)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 9750)
//		NewTone(tonePin, 391, 225.0);
//	else if (millis()<toneTime + 10000)
//		NewTone(tonePin, 293, 450.0);
//	else if (millis()<toneTime + 10750)
//		NewTone(tonePin, 293, 225.0);
//	else if (millis()<toneTime + 11000)
//		NewTone(tonePin, 293, 225.0);
//	else if (millis()<toneTime + 11250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 11500)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 11750)
//		NewTone(tonePin, 391, 225.0);
//	else if (millis()<toneTime + 12000)
//		NewTone(tonePin, 329, 450.0);
//	else if (millis()<toneTime + 12750)
//		NewTone(tonePin, 329, 225.0);
//	else if (millis()<toneTime + 13000)
//		NewTone(tonePin, 329, 225.0);
//	else if (millis()<toneTime + 13250)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 13500)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 13750)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 14000)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 14250)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 14500)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 14750)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 15000)
//		NewTone(tonePin, 659, 225.0);
//	else if (millis()<toneTime + 15250)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 15500)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 15750)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 16000)
//		NewTone(tonePin, 391, 450.0);
//	else if (millis()<toneTime + 16500)
//		NewTone(tonePin, 587, 450.0);
//	else if (millis()<toneTime + 17000)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 17250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 17500)
//		NewTone(tonePin, 493, 450.0);
//	else if (millis()<toneTime + 18000)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 18250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 18500)
//		NewTone(tonePin, 493, 450.0);
//	else if (millis()<toneTime + 19000)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 19250)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 19500)
//		NewTone(tonePin, 391, 337.5);
//	else if (millis()<toneTime + 19875)
//		NewTone(tonePin, 440, 112.5);
//	else if (millis()<toneTime + 20000)
//		NewTone(tonePin, 493, 450.0);
//	else if (millis()<toneTime + 21000)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 21250)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 21500)
//		NewTone(tonePin, 523, 337.5);
//	else if (millis()<toneTime + 21875)
//		NewTone(tonePin, 523, 112.5);
//	else if (millis()<toneTime + 22000)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 22250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 22500)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 22750)
//		NewTone(tonePin, 493, 112.5);
//	else if (millis()<toneTime + 22875)
//		NewTone(tonePin, 493, 112.5);
//	else if (millis()<toneTime + 23000)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 23250)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 23500)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 23750)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 24000)
//		NewTone(tonePin, 440, 450.0);
//	else if (millis()<toneTime + 24500)
//		NewTone(tonePin, 587, 450.0);
//	else if (millis()<toneTime + 25000)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 25250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 25500)
//		NewTone(tonePin, 493, 450.0);
//	else if (millis()<toneTime + 26000)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 26250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 26500)
//		NewTone(tonePin, 493, 450.0);
//	else if (millis()<toneTime + 27000)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 27250)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 27500)
//		NewTone(tonePin, 391, 337.5);
//	else if (millis()<toneTime + 27875)
//		NewTone(tonePin, 440, 112.5);
//	else if (millis()<toneTime + 28000)
//		NewTone(tonePin, 493, 450.0);
//	else if (millis()<toneTime + 29000)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 29250)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 29500)
//		NewTone(tonePin, 523, 337.5);
//	else if (millis()<toneTime + 29875)
//		NewTone(tonePin, 523, 112.5);
//	else if (millis()<toneTime + 30000)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 30250)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 30500)
//		NewTone(tonePin, 493, 225.0);
//	else if (millis()<toneTime + 30750)
//		NewTone(tonePin, 493, 112.5);
//	else if (millis()<toneTime + 30875)
//		NewTone(tonePin, 493, 112.5);
//	else if (millis()<toneTime + 31000)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 31250)
//		NewTone(tonePin, 587, 225.0);
//	else if (millis()<toneTime + 31500)
//		NewTone(tonePin, 523, 225.0);
//	else if (millis()<toneTime + 31750)
//		NewTone(tonePin, 440, 225.0);
//	else if (millis()<toneTime + 32500)
//		NewTone(tonePin, 391, 675.0);
//	else toneTime=millis();
//}


