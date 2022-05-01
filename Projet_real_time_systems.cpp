#include <Servo.h>
#include <Keypad.h>
#include<LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#define SS_PIN 53
#define RST_PIN 5
#define LED_G 23
#define LED_R 22 

// Length of password + 1 for null character
#define Password_Length 5
#define Password_Length1 5

#define LED_G 23
#define LED_R 22 


MFRC522 mfrc522(SS_PIN, RST_PIN);  

Servo myservo;
int buzzer = 12 ;
int led = 8;
int LumiereRouge1 = 41;
int LumiereVerte1 = 4;
int LumiereRouge2 = 7;
int LumiereVerte2 = 6;
int capteur1 = 12;
int capteur2 = 13;
int capteur3 = 31;
int capteur4 = 33;
int capteur5 = 35;
int capteur6 = 37;
int detection1;
int detection2;
int detection3; 
int detection4;
int detection5;
int detection6;

char Data[Password_Length];
char Data1[Password_Length1];
// Password
char Master[Password_Length] = "0000";
char Master1[Password_Length] = "1111";

// Pin connected to lock relay input
int lockOutput = 36;

// Counter for character entries
byte data_count = 0;
byte data_count1 = 0;
// Character to hold key input
char customKey;
char customKey1;

// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connections to Arduino
byte rowPins[ROWS] = {48, 49, 47, 46}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {44, 45, 42, 43};
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int rs = 8, en = 9, d4 = 26, d5 = 27, d6 = 28, d7 = 29;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial mySerial(19, 18);
  void setup() {
  lcd.begin(16, 2);
  
  //lcd.print("Scanner votre");
  //lcd.setCursor(0, 1);
  //lcd.print("carte ou puce");

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myservo.attach(10);
  myservo.write(0);// move servos to center position -> 90°
  
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  lcd.begin(16, 2);
 


  pinMode(led, OUTPUT);
  pinMode(capteur1, INPUT);
  pinMode(capteur2, INPUT);
  pinMode(capteur3, INPUT);
  pinMode(capteur4, INPUT);
  pinMode(capteur5, INPUT);
  pinMode(capteur6, INPUT);
  pinMode(LumiereRouge1, OUTPUT);
  pinMode(LumiereVerte1, OUTPUT);
  pinMode(LumiereRouge2, OUTPUT);
  pinMode(LumiereVerte2, OUTPUT);
  pinMode (buzzer, OUTPUT) ;
  // Set lockOutput as an OUTPUT pin
  pinMode(lockOutput, OUTPUT);
  

}
void loop() {
  char customKey = customKeypad.getKey();
   
  detection1 = digitalRead(capteur1);
  detection2 = digitalRead(capteur2);
  detection3 = digitalRead(capteur3);
  detection4 = digitalRead(capteur4);
  detection5 = digitalRead(capteur5);
  detection6 = digitalRead(capteur6);
  // Si on détecte une personne, on allume la LED
  // Si on ne détecte personne, on éteint la LED
  //if (customKey){
    //Serial.println(customKey);


  // Initialize LCD and print
  lcd.setCursor(0, 0);
  lcd.print("Entrer MDP:");

  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  // See if we have reached the password length
  if (data_count == Password_Length - 1) {
    lcd.clear();

    if (strcmp(Data, Master)==0) {
      // Password is correct
      digitalWrite(lockOutput, HIGH);
      //lcd.print("Bienvenue");
      // Turn on relay for 5 seconds
      digitalWrite(LED_G, HIGH);
      //delay(500);
      digitalWrite(lockOutput, HIGH);
      //digitalWrite(LED_G, LOW);
      lcd.clear();





    }
  
    
   

    else {
      // Password is incorrect
      digitalWrite(LED_R, HIGH);
      lcd.print("Incorrect");
      delay(1000);
      digitalWrite(LED_R, LOW);
    }

    if(detection3 == 0 ){
  

      if(detection4 == 0){
      //myservo.write(90);// move servos to center position -> 90°
      //delay(500);
      
      digitalWrite(LumiereRouge2, HIGH);
      digitalWrite(LumiereVerte2, LOW);

      
      if(detection2 == 0){//capteurs 2, 3, 4 
      myservo.write(90);
      digitalWrite (buzzer, HIGH) ; //send tone
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("veuillez");
      lcd.setCursor(0, 1);
      lcd.print("patientez SVP");
      delay(500);
      digitalWrite (buzzer, LOW) ;
      digitalWrite(LumiereRouge1, LOW);
      digitalWrite(LumiereVerte1, HIGH);
      }
      else if((detection5==0)||(detection6==0)){//capteurs 3,4,5 ou capteurs 3,4,6
      digitalWrite(LumiereRouge1, LOW);
      digitalWrite(LumiereVerte1, HIGH);
      digitalWrite (buzzer, HIGH) ;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("veuillez");
      lcd.setCursor(0, 1);
      lcd.print("patientez SVP");
      delay(500);
      myservo.write(90);
      digitalWrite (buzzer, LOW) ;
      }
      else {
        
        //juste les capteurs 3 et 4
      digitalWrite (buzzer, HIGH) ;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("veuillez");
      lcd.setCursor(0, 1);
      lcd.print("patientez SVP");
      delay(500);
      //myservo.write(90);
      digitalWrite (buzzer, LOW) ;
      //myservo.write(90);
      //delay(1000);
      digitalWrite(LumiereRouge1, LOW);
      digitalWrite(LumiereVerte1, HIGH);
      

      }
    }
  
    else{
       //obstacle juste le capteur 3

    digitalWrite (buzzer, HIGH) ;
   
    digitalWrite(LumiereRouge1, HIGH);
    digitalWrite(LumiereVerte1, LOW);
    digitalWrite(LumiereRouge2, HIGH);
    digitalWrite(LumiereVerte2, LOW);
    myservo.write(0);
    delay(4000);
    digitalWrite (buzzer, LOW) ;
    
       //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(1200); // Même vitesse du port série que la carte SIM800L
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(1200);  // Vitesse du port série pour les cartes SIM de 3G

  Serial.println("Initializing..."); 
  //delay(1000);  // Délai d'une seconde pour les cartes SIM de 3G.
 
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  
  mySerial.println("AT+CMGS=\"+18193293450\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  
  mySerial.print("Anomalie du systeme"); //text content
  Serial.println("Voici le message envoyé :...."); // Message affiché sur le moniteur série
  updateSerial();
  
    mySerial.write(26);
    
    }
  }
  else if(detection5 == 0){
    if((detection4 == 0)||(detection6 == 0)){
    digitalWrite(LumiereRouge2, HIGH);
    digitalWrite(LumiereVerte2, LOW);
    digitalWrite (buzzer, HIGH) ;
    digitalWrite(LumiereRouge1, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("veuillez");
    lcd.setCursor(0, 1);
    lcd.print("patientez SVP");
    delay(500);
    myservo.write(90);
    digitalWrite (buzzer, LOW) ;

    //myservo.write(90);
    
    
    digitalWrite(LumiereVerte1, HIGH);
    }
    else{
      //juste le capteur 5
    digitalWrite(LumiereRouge1, HIGH);
    digitalWrite(LumiereVerte1, LOW);
    myservo.write(0);
    delay(500);
    digitalWrite(LumiereRouge2, LOW);
    digitalWrite(LumiereVerte2, HIGH);
    }
  }
  else if((detection4==0) && (detection6==0)){//les capteur 4 et 6
  digitalWrite(LumiereRouge2, HIGH);
  digitalWrite(LumiereVerte2, LOW);
  digitalWrite (buzzer, HIGH) ;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("veuillez");
  lcd.setCursor(0, 1);
  lcd.print("patientez SVP");
  delay(500);
  myservo.write(90);
  digitalWrite (buzzer, LOW) ;
  //myservo.write(90);
  //delay(1000);
  digitalWrite(LumiereRouge1, LOW);
  digitalWrite(LumiereVerte1, HIGH);
  
  
  }
  else{
    //fonctionnement en abscence du train 
  digitalWrite(LumiereRouge1, HIGH);
  digitalWrite(LumiereVerte1, LOW);
  delay(500);
  digitalWrite(LumiereRouge2, LOW);
  digitalWrite(LumiereVerte2, HIGH);
  delay(5000);
  myservo.write(0);
  }  
  }

    // Clear data and LCD display
    //lcd.clear();
    //clearData();







}


void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }


  
}


void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}
