
#include <LiquidCrystal.h>
#include <Servo.h>

#define  LM335_pin  0 
#define buzzer 12
#define ledSari 10
#define ledYesil 8
#define ledKirmizi 11
#define butonSistem 14
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Servo klimaKapak; 
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {17, 18, 19, 20}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {14, 15, 16}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int sistem=0;
int i = 0;
int fan = 13;
boolean butonDurum=0;
boolean ledDurum=0;
boolean klimaIf = false;
boolean fanIf = false;

void setup() {
  lcd.begin(16, 2);
  klimaKapak.attach(9);
  pinMode(fan, OUTPUT);
  pinMode(ledKirmizi,OUTPUT);
  pinMode(ledSari,OUTPUT);
  pinMode(ledYesil,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(butonSistem, OUTPUT);
}
 
char message1[] = "Temp =  00.0 C";
int  Celsius;
void loop() {
  if(sistem == 0){
  lcdMenu(); 
  sistem=1; 
  }
  char key = keypad.getKey();
  if(key){
  if(key=='*'){
  lcdMenu();
  }
  
  if(key=='3'){
    klimaIf=true;
  klimaYonlendirmeServo();
  }
  
  }
  if(klimaIf==true){
    klimaYonlendirmeServo();
    }
  if(key=='1'){
    fanKontrolu();
    fanIf=true;
  }
  if(key=='6'){
    
    klimaIf=false;
    
  }
  
  sicaklikOlc();
  if(fanIf==true){
  fanKontrolu();
    if(key=='4'){
      fanIf=false;
    }
  }
  
  sicaklikKontrol();
  uykuKorumaModu();
   
}
void lcdMenu(){

lcd.setCursor(i,0);
lcd.print("Fan=1 Sicaklik=2"); 
lcd.setCursor(i,1);
lcd.print("Yonlendirme=3"); 
delay(2000);
lcd.clear();
lcd.setCursor(i,0);
lcd.print("fanKapa=4"); 
lcd.setCursor(i,1);
lcd.print("yonlendirKapa=6"); 
delay(2000);
lcd.clear();
lcd.setCursor(i,0);
lcd.print("menu=*"); 
lcd.setCursor(i,1);
lcd.print(""); 
delay(2000);
lcd.clear();
}

}

void klimaYonlendirmeServo(){

    for( i = 0;i<=180;i+=1){
      klimaKapak.write(i);
      delay(15);
    }

    
    for( i = 180;i >= 0; i-=1){
      klimaKapak.write(i);
      delay(15);
    }
}

void uykuKorumaModu(){
  int isik = analogRead(A1);
  delay(50);

  if(isik < 10){
    digitalWrite(ledSari,HIGH);
  }

  else{
    digitalWrite(ledSari,LOW);
  }  
}

void sicaklikKontrol(){
  if(Celsius >= 40|| Celsius <= -10){
    digitalWrite(ledKirmizi,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(50);
    digitalWrite(ledKirmizi,LOW);
    digitalWrite(buzzer,LOW);
    delay(50);
  }
  else{

    digitalWrite(ledKirmizi,LOW);
    digitalWrite(buzzer,LOW);
    
    
  }
}
void fanKontrolu () {
  //if(Celsius<20){
    if(fanIf==false){
    digitalWrite(fan,LOW);
  }
  else{
    digitalWrite(fan,HIGH);
  }
}
void sicaklikOlc(){

  
  delay(1000);                                 
  
  Celsius = analogRead(LM335_pin) * 0.489 - 273;                      
  if(Celsius < 0){
    Celsius = abs(Celsius);                    
    message1[7] = '-';                         
  }
  else
    message1[7]  = ' ';                        
  if (Celsius > 99)
    message1[7]  = '1';                        
  message1[8]  = (Celsius / 10) % 10  + 48;
  message1[9]  =  Celsius % 10  + 48;
  message1[12] =  223;                        
  lcd.setCursor(0, 0);
  lcd.print(message1);
  lcd.setCursor(5, 1);
  //lcd.print(message2);
}
