#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

long pingd[10], hcsrd[10];
int index = 0;
long ping, pingfinal, oldping, hcsr, hcsrfinal, oldhcsr;
int pingpin = 13;
int trigpin = 7;
int echopin = 8;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  for(int i=0; i<10; i++) {
    pingd[i] = 0;
    hcsrd[i]=0;
  }
  ping = 0;
  hcsr=0;
  pingfinal = 0;
  hcsrfinal =0;
  oldping = 0;
  oldhcsr = 0;
}

void loop() {
  lcd.display();
  
  if(index >= 10) {
    lcd.setCursor(0,0);
    lcd.print("      ");
    lcd.setCursor(0,1);
    lcd.print("      ");
    index = 0;
    oldping = 0;
    oldhcsr = 0;
    pingfinal = ping/10;
    hcsrfinal = hcsr/10;
    //Serial.println(pingfinal + "//" + hcsrfinal);
  }
  
  pinMode(pingpin,OUTPUT);
  digitalWrite(pingpin, LOW);
  delay(2);
  digitalWrite(pingpin,HIGH);
  delay(5);
  digitalWrite(pingpin,LOW);
  
  pinMode(pingpin,INPUT);
  pingd[index] = pulseIn(pingpin,HIGH);
  ping = oldping + pingd[index];
  
  delay(5);
  
  pinMode(trigpin,OUTPUT);
  digitalWrite(trigpin,LOW);
  delay(2);
  digitalWrite(trigpin,HIGH);
  delay(5);
  digitalWrite(trigpin,LOW);
  
  pinMode(echopin, INPUT);
  hcsrd[index] = pulseIn(echopin, HIGH);
  hcsr = oldhcsr + hcsrd[index];
  
  index = index + 1;
  oldping = ping;
  oldhcsr = hcsr;
  
  lcd.setCursor(0,0);
  lcd.print(pingfinal);
  lcd.setCursor(0,1);
  lcd.print(hcsrfinal);
  
  delay(500);
}

