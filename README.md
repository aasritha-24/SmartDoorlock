# Arduino Door Lock Security System
This is an advanced door lock system implemented using Arduino, featuring a keypad interface, LCD display, servo motor, and LED indicators. The project provides secure access control with multiple security features.
## Hardware Components
* Arduino Board
* 4x4 Keypad
* 16x2 LCD Display
* Servo Motor
* Red and Green LEDs
* Jumper Wires
* Breadboard
## Working principle
1. Initial Setup 
 * The system starts with a predefined password: "12347890" 
 * LCD displays a welcome message 
 * The door is initially locked (red LED on, servo at 90 degrees) 

2. Password Entry Process 
 * User enters an 8-digit password on the keypad 
 * Each digit is masked with an asterisk (*) on the LCD 
 * Special keys have unique functions:  
      - '*' key: Resets current password entry
      - '#' key: Deletes last entered digit 
      - 'A', 'B', 'C' keys: Default passwords set by manufacturer 
      - 'D' key: Full password change mechanism 

3. Password Validation
   * System checks each entered digit against the stored password 
   * If any digit is incorrect, a "wrong" counter increments
   * After 8 digits are entered, the system determines:
   * Correct password: Door opens (green LED, servo rotates)
   * Incorrect password: Door remains locked (red LED) 

4. Security Features
   * 3 consecutive wrong attempts trigger a 5-second lockout period
   * Password can be changed securely by first entering the old password
   * Servo motor physically controls the lock mechanism 

5. Lock/Unlock Mechanism
   * setLocked() function manages the lock state  
   * When locked: Red LED on, servo at 90 degrees 
   * When unlocked: Green LED on, servo rotates to open position 
   * Automatically relocks after 10 seconds 

