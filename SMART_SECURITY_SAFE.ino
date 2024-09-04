#define CUSTOM_SETTINGS 
#define INCLUDE_TERMINAL_MODULE 
#include <Dabble.h> 
#include <Keypad.h> 
#include <LiquidCrystal.h> 
#define Password_Length 5 
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); 
String Serialdata = ""; 
bool dataflag = 0; 
int pos = 0; 
char Data[Password_Length]; 
char Master[Password_Length] = "1190"; 
char Master1[Password_Length] = "1290"; 
char Master2[Password_Length] = "1390"; 
byte data_count = 0, master_count = 0; 
bool Pass_is_good, break_loop=0; 
bool door = false; 
char customKey; 
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = { 
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'}, 
  {'*', '0', '#', 'D'} 
}; 
byte rowPins[ROWS] = {4, 5, 6, 7}; 
byte colPins[COLS] = {8, 9, 10, 11}; 
 
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
void setup() 
{ 
  lcd.begin(16, 2); 
  Dabble.begin(9600); 
  Serial.begin(9600); 
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT); 
} 
void loop() 
{ 
  Dabble.processInput();  
  if (door == true) 
  { 
    customKey = customKeypad.getKey(); 
    if (customKey == '#') 
    { 
      lcd.clear(); 
      door = false; 
    } 
  } 
  else 
    Open(); 
} 
void loading (char msg[]) { 
  lcd.setCursor(0, 1); 
  lcd.print(msg); 
 
  for (int i = 0; i < 9; i++) { 
    delay(1000); 
    lcd.print("."); 
  } 
} 
void clearData() 
{ 
  while (data_count != 0) 
  {  
    Data[data_count--] = 0; 
  } 
  return; 
} 
void Open() 
{ 
  lcd.setCursor(0, 0); 
  lcd.print("Enter Password"); 
  customKey = customKeypad.getKey(); 
  if(Terminal.available()) 
  { 
    while (Terminal.available() != 0) 
    { 
      Data[data_count] = Terminal.read(); 
      data_count++; 
    } 
    dataflag = 1; 
  } 
  else if (customKey) 
  { 
    do 
    { 
      if (customKey) 
      { 
        if (customKey == 'C') 
        { 
          clearData(); 
          break_loop = 1; 
          lcd.clear(); 
          break; 
        } 
        Data[data_count] = customKey; 
        lcd.setCursor(data_count, 1); 
        lcd.print(Data[data_count]); 
        data_count++; 
      } 
      customKey = customKeypad.getKey(); 
    }while (!(data_count == (Password_Length - 1))); 
    if (!break_loop) 
      dataflag = 1; 
  } 
  if (dataflag) 
  { 
    if (!strcmp(Data, Master)) 
    { 
      lcd.clear(); 
      lcd.setCursor(0, 0); 
      lcd.print(" Safe is Open"); 
      door = true; 
      digitalWrite(12, HIGH); 
      digitalWrite(13, HIGH); 
      _delay_ms(500); 
      digitalWrite(13, LOW); 
      lcd.setCursor(2, 1); 
      lcd.print("HELLO RAZA"); 
       Terminal.print("Raza Opened the safe"); 
      _delay_ms(5000); 
      lcd.clear(); 
      lcd.setCursor(1, 0); 
      lcd.print("Safe is Closed"); 
       digitalWrite(13, HIGH); 
      _delay_ms(500); 
      digitalWrite(13, LOW); 
      digitalWrite(12, LOW); 
      _delay_ms(500); 
      door = false;  
      dataflag = 0;      
    } 
    else if(!strcmp(Data, Master1)) 
    { 
      lcd.clear(); 
      lcd.setCursor(0, 0); 
      lcd.print(" Safe is Open"); 
      door = true; 
      digitalWrite(12, HIGH); 
      digitalWrite(13, HIGH); 
      _delay_ms(500); 
      digitalWrite(13, LOW); 
      lcd.setCursor(2, 1); 
      lcd.print("HELLO HASEEB"); 
      Terminal.print("Haseeb Opened the safe"); 
      _delay_ms(4500); 
      lcd.clear(); 
   lcd.setCursor(1, 0); 
      lcd.print("Safe is Closed"); 
       digitalWrite(13, HIGH); 
      _delay_ms(500); 
      digitalWrite(13, LOW); 
      digitalWrite(12, LOW); 
      _delay_ms(500); 
      door = false;  
      dataflag = 0;  
    } 
     else if(!strcmp(Data, Master2)) 
    { 
      lcd.clear(); 
      lcd.setCursor(0, 0); 
      lcd.print(" Safe is Open"); 
      door = true; 
      digitalWrite(12, HIGH); 
      digitalWrite(13, HIGH); 
      _delay_ms(500); 
      digitalWrite(13, LOW); 
      lcd.setCursor(2, 1); 
      lcd.print("HELLO OBAID"); 
      Terminal.print("Obaid Opened the safe"); 
      _delay_ms(4500); 
      lcd.clear(); 
      lcd.setCursor(1, 0); 
      lcd.print("Safe is Closed"); 
       digitalWrite(13, HIGH); 
      _delay_ms(500); 
      digitalWrite(13, LOW); 
      digitalWrite(12, LOW); 
      _delay_ms(500); 
      door = false;  
      dataflag = 0;  
    } 
    else 
    { 
      lcd.clear(); 
      lcd.print(" Wrong Password "); 
      digitalWrite(13, HIGH); 
      _delay_ms(3000); 
      digitalWrite(13, LOW); 
      door = false; 
dataflag = 0;  
} 
delay(1000); 
lcd.clear(); 
clearData(); 
} 
}