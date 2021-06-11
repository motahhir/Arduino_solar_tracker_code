/*****************************************************************************
         Copyright  Motahhir  All Rights Reserved
*****************************************************************************/

/*****************************************************************************
   Header Files included
 *****************************************************************************/

/******************************************************************************
   PROJECT :  Solar trcker algorithm implementation
   
 ******************************************************************************
 *                                                                            *
    Written by  :  Aboubakr El Hammoumi and Saad Motahhir    Date : 09/10/2017
 *                                                                            *
    Email : saad.motahhir@usmba.ac.ma
 ******************************************************************************
   MODIFICATION LOG:
 ******************************************************************************
   Modified by :                                           Date :
   Comments :
 ******************************************************************************/
#include <LiquidCrystal.h>
#include <Servo.h>




Servo servo_x;               //definition de servo up-down   
int servoh = 0;
int servohLimitHigh = 170;     
int servohLimitLow = 10;       

Servo servo_z;              //definition de servo left-right
int servov = 0; 
int servovLimitHigh = 170;
int servovLimitLow = 10;

/*Affectation des capteurs LDR*/
int topl,topr,botl,botr;
int threshold_value=20;        //measurement sensitivity


float Vout;

void setup()
{
  Serial.begin(9600);
  servo_x.attach(5);
  servo_z.attach(6);
//  pinMode(2,OUTPUT);
//  digitalWrite(2,LOW); 
}

void loop()
{

 
    servoh = servo_x.read();
    servov = servo_z.read();
      
     //capturing analog values of each LDR
     topr= analogRead(A2);         //capturing analog value of top right LDR
     topl= analogRead(A3);         //capturing analog value of top left LDR
     botl= analogRead(A4);         //capturing analog value of bot left LDR
     botr= analogRead(A5);         //capturing analog value of bot right LDR

//     Vout=(analogRead(A1) * 5.0) / 1023;


//    if (digitalRead(2)==HIGH){
//    Serial.println(" Automatic");

    // calculating average
    int avgtop = (topr + topl) / 2;     //average of top LDRs
    int avgbot = (botr + botl) / 2;     //average of bottom LDRs
    int avgright = (topr + botr) / 2;   //average of right LDRs
    int avgleft = (topl + botl) / 2;    //average of left LDRs
//    int avgsum = (avgtop+avgbot+avgright+avgleft)/4;  
//    delay(10);
    
    //Get the different 
    int diffhori= avgtop - avgbot;      //Get the different average betwen LDRs top and LDRs bot
    int diffverti= avgleft - avgright;    //Get the different average betwen LDRs right and LDRs left

//    Serial.print(" diffhori ");
//    Serial.println(diffhori);
//    Serial.print(" diffverti ");
//     Serial.println(diffverti);
//    
   
    
    /*tracking in horizontal axis*/ 
    if (abs(diffhori) <= threshold_value)
    {
     servo_x.write(servoh);                    //stop the servo up-down
    }else {
          if (diffhori > threshold_value)
           
          { Serial.println(" x - 2 ");
          servo_x.write(servoh -2);            //Clockwise rotation  CW
          if (servoh > servohLimitHigh)
          {
           servoh = servohLimitHigh;
          }
          delay(10);
          }else {Serial.println(" x + 2 ");
                 servo_x.write(servoh +2);     //CounterClockwise rotation  CCW
                 if (servoh < servohLimitLow)
                 {
                 servoh = servohLimitLow;
                 }
                 delay(10);
                 }
           }      
    /*tracking in vertical axis*/ 
    if (abs(diffverti) <= threshold_value)
    {     
     servo_z.write(servov);                   //stop the servo motor left-right
    }else{
          if (diffverti > threshold_value)
          {  Serial.println(" z - 2 ");
             servo_z.write(servov -2);        //Clockwise rotation  CW
             if (servov > servovLimitHigh) 
             { 
             servov = servovLimitHigh;
             }
             delay(10);
          } else{
                 Serial.println(" z + 2 ");
                 servo_z.write(servov +2);    //Counterclockwise rotation  CCW
                 if (servov < servovLimitLow) 
                 {
                 servov = servovLimitLow;
                 }
                 delay(10);
                 }
          }
 }



  
