// include the library code:
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 4, 3, 2);

long readUltrasonicDistance(int triggerPin, int echoPin) {
    pinMode(triggerPin, OUTPUT);  // Clear the trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    // Reads the echo pin, and returns the sound wave travel time in microseconds
    return pulseIn(echoPin, HIGH);
}

int counter;

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT); //Light Sensor
    pinMode(10, OUTPUT); //Red LED
    pinMode(9, OUTPUT); //Yellow LED
    pinMode(8, OUTPUT); //Green LED
    pinMode(5, OUTPUT); //Buzzer
    lcd.begin(16, 2);
    lcd.clear();
}

void loop() {
    if (analogRead(A0) >= 800) {

        while (0.01723 * readUltrasonicDistance(7, 6) > 10) {
            lcd.setCursor(0, 0);
            lcd.print("Regular Mode");
            digitalWrite(10, HIGH);//Red LED
            delay(2000); // Wait for 2 seconds
            digitalWrite(10, LOW);
            digitalWrite(9, HIGH);//Yellow LED
            delay(1000); // Wait for 1 second
            digitalWrite(9, LOW);
            digitalWrite(8, HIGH);//Green LED
            delay(2000); // Wait for 2 seconds
            digitalWrite(8, LOW);
            digitalWrite(9, HIGH);//Yellow LED
            delay(1000); // Wait for 1 seconds
            digitalWrite(9, LOW);
        }

        if (0.01723 * readUltrasonicDistance(7, 6) < 10) {
            digitalWrite(10, HIGH);
            delay(2000); // Wait for 2000 millisecond(s)
            digitalWrite(10, LOW);
            digitalWrite(9, HIGH);
            delay(1000); // Wait for 1000 millisecond(s)
            digitalWrite(9, LOW);
            digitalWrite(8, HIGH);
            delay(2000); // Wait for 2000 millisecond(s)
            digitalWrite(8, LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Pedestrain Mode");
            delay(1000);
            lcd.clear();

            for (counter = 0; counter < 10; ++counter) {
                lcd.setCursor(1, 0); // display the text in what line (i.e. 0 line and 0 space)
                lcd.print("CROSS NOW!"); //print text on LCD
                Serial.println("CROSS NOW!"); //checks if the text is displayed
                delay(100);
                digitalWrite(9, HIGH);
                tone(5, 1000); // play tone 1000
                delay(100); // Wait for 100 millisecond(s)
                // set the cursor to column 0, line 1
                // (note: line 1 is the second row, since counting begins with 0):
                digitalWrite(9, LOW);
                delay(100); // Wait for 100 millisecond(s)
                noTone(5);
                lcd.clear();
            }
        }
    }

    else {
        lcd.setCursor(0, 0);
        lcd.print("Night Mode");
        delay(1000);
        lcd.clear();
        if (0.01723 * readUltrasonicDistance(7, 6) > 60) {
            lcd.setCursor(0, 0);
            lcd.print("No Object");
            delay(1000);
            lcd.clear();
            digitalWrite(10, HIGH);
            digitalWrite(8, LOW);
        }
        if (0.01723 * readUltrasonicDistance(7, 6) < 60) {
            lcd.setCursor(0, 0);
            lcd.print("Object Detected");
            delay(1000);
            lcd.clear();
            digitalWrite(10, LOW);
            digitalWrite(8, HIGH);
        }
    }

    delay(1000); // Wait for 1000 millisecond(s)

    analogRead(A0);

    analogRead(A0);
}