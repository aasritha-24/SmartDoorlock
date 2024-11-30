#include <Keypad.h>  // KEYPAD LIBRARY FOR KEYPAD INTERFACING
#include <LiquidCrystal.h>
#include <Servo.h>  // LIBRARY FOR SERVO MOTOR

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char keys[4][4] = {
  {'1','4','7','*'},
  {'2','5','8', '0'},
  {'3','6','9', '#'},
  {'A','B','C', 'D'}
};

byte rowPin[4] = {5, 4, 3, 2}; // ROW PINS OF KEYPAD
byte colPin[4] = {9, 8, 7, 6}; // COLUMN PINS OF KEYPAD

Servo servo_Motor;

String password = "12347890";  // INITIAL PASSWORD
String R_pass;
int position = 0; // VARIABLE FOR DETERMINING THE POSITION
int wrong = 0; // VARIABLE FOR CALCULATING THE WRONG INPUT
int reset_pos = 0, i = 0; // FOR IMPROVEMENTS LATER ON
int reset_wrong = 0;
int reset_total = 0;

int redPin = 13; // DEFINING PIN FOR RED LED
int greenPin = 1; // DEFINING PIN FOR GREEN LED

Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, 4, 4);

int total = 0; // VARIABLE TO DETERMINE THE NUMBER OF WRONG ATTEMPTS

// FORWARD DECLARATION OF setLocked FUNCTION
void setLocked(bool locked);

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("DOOR LOCK SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("BY IIT BBS");
  delay(2000);
  lcd.clear();
  setLocked(true);
  delay(500);
}

void loop() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Enter Password:");
  for(int i=0;i<position;i++){
    lcd.setCursor(i, 1);
    lcd.print('*');
  }
  delay(100);
  
  char pressed = keypad.getKey(); // TAKING KEY INPUT
  
  if (pressed) {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("Enter Password:");
    for(int i=0;i<position+1;i++){
    lcd.setCursor(i, 1);
    lcd.print('*');
    }
    delay(500);
    
    if (pressed == '*') {
      position = 0;
      setLocked(true);
      lcd.clear();
    }
    else if (pressed == 'A') {
      password = "98765432"; // Change password
    }
    else if (pressed == 'B') {
      password = "76582347"; // Change password
    }
    else if (pressed == 'C') {
      password = "12347890"; // Change password
    }
    else if (pressed == 'D') { // Change password functionality
      lcd.begin(16,2);
      lcd.clear();
      lcd.print("Enter Old Pass:");
      lcd.setCursor(0, 1);
    delay(500);
      String enteredOldPass = "";
      int position=0;
      // Wait for the old password to be entered
      while (enteredOldPass.length() < 8) {
        char temp = keypad.getKey();
        if (temp) {
          enteredOldPass += temp;
          lcd.begin(16,2);
          lcd.print("Enter Old Pass:");
          position++;
           for(int i=0;i<position;i++){
            lcd.setCursor(i, 1);
          lcd.print('*');}
        }
      
        
      }

      if (enteredOldPass == password) { // If old password is correct
        lcd.clear();
        lcd.print("Enter New Pass:");
        String newPass = "";
         int position =0;
        // Wait for the new password to be entered
        while (newPass.length() < 8) {
          char temp = keypad.getKey();
          if (temp) {
            newPass += temp;
            lcd.begin(16,2);
             lcd.print("Enter New Pass:");
            position++;
             for(int i=0;i<position;i++){
              lcd.setCursor(i, 1);
            lcd.print("*");}
          }
        }

        password = newPass; // Update the password
        lcd.clear();
        lcd.print("Password Changed!");
        delay(2000);
      } else {
        lcd.clear();
        lcd.print("Wrong Old Pass!");
        delay(2000);
      }

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Password:");
      for(int i=0;i<position+1;i++){
        lcd.setCursor(i, 1);
        lcd.print('*');
      }
      position = 0;
      R_pass = "";
    } 
    else if (pressed == '#') {
      if (position > 0) position--; // Clear last digit
    }
    else if (pressed == password[position]) {
      R_pass += pressed;
      position++;
    }
    else {
      wrong++;
      position++;
    }
    
    if (position == 8) { // When full password is entered
      if (wrong > 0) {
        total++;
        wrong = 0;
        position = 0;
        lcd.clear();
        lcd.print("WRONG");
        lcd.setCursor(5, 1);
        lcd.print("PASSWORD");
        setLocked(true);
        delay(1000);
        R_pass = ""; // Reset entered password
      }
      else if (position == 8 && wrong == 0) {
        position = 0;
        wrong = 0;
        lcd.clear();
        lcd.print("PASSWORD");
        lcd.setCursor(6, 1);
        lcd.print("ACCEPTED");
        delay(2000);
        lcd.clear();
        lcd.print("Door Open");
        setLocked(false);
        delay(2000);
        R_pass = ""; // Reset entered password
        setLocked(true);
      }
      
      if (total == 3) { // If 3 wrong attempts
        total = 0;
        delay(500);
        lcd.begin(16,2);
        lcd.clear();
        lcd.print("wait 5 sec");
         delay(5000);
      }
    }
  }
}

// FUNCTION TO CHANGE STATUS OF SERVO MOTOR
void setLocked(bool locked) {
  if (locked) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    delay(1000);
    servo_Motor.attach(10);
    servo_Motor.write(90);
    delay(1000);
    servo_Motor.detach();
  }
  else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    delay(1000);
    servo_Motor.attach(10);
    servo_Motor.write(-90);
    delay(1000);
    servo_Motor.detach();
    delay(10000);
    digitalWrite(greenPin, LOW);
  }
}