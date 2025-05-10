  #include <LiquidCrystal_I2C.h>

   LiquidCrystal_I2C lcd(0x38,16,2);
const int yakitSensor = A2;

  
  int startbutondurum;
  int kemerdurum;
  float sicaklik;
  int ldrdeger;
  int start = 9;
  int kemer = 10;
  int kapi = 11;
  int kled = 8;
  int far = 7;
  int rgbR = 6;
  int rgbG = 5;
  int rgbB = 4;
  int buzzer = 2;
  int ww15tsi = 3;
  int LM35 = A0;
  int klimafan = 53;
  int ldr = A1;
  
void setup() 
{
  lcd.begin();

  pinMode(start , INPUT);
  pinMode(kemer , INPUT);

  pinMode(kled , OUTPUT);
  pinMode(far , OUTPUT);
  pinMode(rgbR , OUTPUT);
  pinMode(rgbG , OUTPUT);
  pinMode(rgbB , OUTPUT);
  pinMode(buzzer , OUTPUT);
  pinMode(ww15tsi , OUTPUT);
  pinMode(klimafan , OUTPUT);

}

void loop() 
{
  int potDeger = analogRead(yakitSensor);
  int yakitYuzde = map(potDeger, 0, 1023, 0, 100);
int kapidurum = digitalRead(kapi);
sicaklik = ((analogRead(LM35)* (5000/1024.0))/10);
startbutondurum = digitalRead(start);
kemerdurum = digitalRead(kemer);
ldrdeger = analogRead(ldr);

if (startbutondurum == HIGH)  
  {
    if (kemerdurum == HIGH)
    {
      digitalWrite(ww15tsi , HIGH);
      digitalWrite(kled , LOW);
      digitalWrite(buzzer , LOW);}
    
    if (kemerdurum == LOW)
    {
      digitalWrite(kled , HIGH);
      digitalWrite(buzzer , HIGH);
      digitalWrite(ww15tsi , LOW);
      }

  }

if (kemerdurum == HIGH){
      digitalWrite(kled , LOW);
      digitalWrite(buzzer , LOW);
      }

if (sicaklik >= 25){
      digitalWrite(klimafan , HIGH);
      lcd.setCursor(0,0); // İlk satırın başlangıç noktası
      lcd.print("Sicaklik: "); 
      lcd.print(sicaklik);
      lcd.setCursor(0,1);
      lcd.print("Klima Acildi"); 
      }

    if (sicaklik < 25){
      digitalWrite(klimafan , LOW);
     
      }


if (ldrdeger > 250 && digitalRead(far) == 1){
      lcd.clear ();
      digitalWrite(far , LOW);
      lcd.print("FAR KAPALI"); 
      delay (1000);
      lcd.clear (); }

if (ldrdeger <= 250 && digitalRead(far) == 0 && yakitYuzde != 0){
      digitalWrite(far , HIGH);
      lcd.clear ();
      lcd.print("FAR ACIK"); 
      }

if (yakitYuzde == 0) {
   
    digitalWrite(ww15tsi, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Yakit Bitti     ");
    lcd.setCursor(0, 1);
    lcd.print("Motor Durdu     ");

    digitalWrite(kled, LOW);
    digitalWrite(far, LOW);
    analogWrite(rgbR, 0);
    analogWrite(rgbG, 0);
    analogWrite(rgbB, 0);
}

else if (yakitYuzde < 5 && yakitYuzde != 0 ) {

    lcd.setCursor(0, 1);
    lcd.print("Uyr:Yakit %5 ");

    analogWrite(rgbR, 255);   
    analogWrite(rgbG, 255); 
    analogWrite(rgbB, 0);   
    delay(500);

    analogWrite(rgbR, 0);   
    analogWrite(rgbG, 0);
    delay(500);} 

else if (yakitYuzde < 10) {
  
    lcd.setCursor(0, 1);
    lcd.print("Uyr:Yakit %10");

    analogWrite(rgbR, 255);
    analogWrite(rgbG, 255);
    analogWrite(rgbB, 0);
  } 
  else if (kapidurum != LOW) {
    analogWrite(rgbR, 0);
    analogWrite(rgbG, 0);
    analogWrite(rgbB, 0);
    lcd.setCursor(0, 1);
    lcd.print("                ");

  }

  if (kapidurum == LOW) {
   
    analogWrite(rgbR, 255);
    analogWrite(rgbG, 0);
    analogWrite(rgbB, 255);

    lcd.setCursor(0, 0);
    lcd.print("Uyari: Kapı Acik");
    lcd.setCursor(0, 1);
    lcd.print("Motor Calismaz ");
    digitalWrite(ww15tsi, LOW);
} 
else { 
    analogWrite(rgbR, 0);
    analogWrite(rgbG, 0);
    analogWrite(rgbB, 0);

    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
}


  }






    












