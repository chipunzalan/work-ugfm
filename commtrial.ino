#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

int pingd[10];
int ping, pingfinal, oldping;
int index=0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  establishContact();
}

void loop() {
  lcd.display();
  if(index >= 10) {
    lcd.setCursor(0,0);
    lcd.print("      ");
    
    pingfinal = ping/10;
    index = 0;
    oldping = 0;
    String thisString = String(pingfinal,BIN);
//    Serial.println(thisString+"/");
//    Serial.write(pingfinal);
    int cnt = pingfinal;
    byte data[11];
    thisString.getBytes(data,11);
//    Serial.print(pingfinal );
//    Serial.print("//"+thisString + "//");
    Serial.write(data,11);
//    Serial.println();
//    byte temp1 = (cnt & 0xFF);
//    byte temp2 = ((cnt >> 8));
//    Serial.write(temp1);
//    Serial.write(temp2);
//    Serial.println(temp1 + "////" + temp2);
//    Serial.println("- - - - - - ");
  }
  
  pinMode(7,OUTPUT);
  digitalWrite(7, LOW);
  delay(2);
  digitalWrite(7,HIGH);
  delay(5);
  digitalWrite(7,LOW);
  
  pinMode(7,INPUT);
  pingd[index] = pulseIn(7,HIGH);
  ping = oldping + pingd[index];
  
  index = index + 1;
  oldping= ping;
  
//  Serial.print(index);
//  Serial.print(" // ");
//  Serial.print(pingd[index]);
//  Serial.print(" // ");
//  Serial.print(oldping);
//  Serial.print(" // ");
//  Serial.print(ping);
//  Serial.print(" // ");
//  Serial.println(pingfinal);
  
  lcd.setCursor(0,0);
  lcd.print(pingfinal);
  
  delay(100);
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.write('A');   // send a capital A
    delay(100);
  }
}
