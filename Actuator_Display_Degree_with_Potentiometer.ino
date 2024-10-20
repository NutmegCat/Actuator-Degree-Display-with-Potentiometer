#include <Arduino.h>
#include <U8x8lib.h>
#include <Servo.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE);
Servo myservo;   // create Servo object to control a servo
int potpin = A0; // analog pin used to connect the potentiometer
int val;         // variable to read the value from the analog pin
int prevVal = 0; // variable to store previous value

void setup(void)
{
    u8x8.begin();
    u8x8.setFlipMode(1); // Flip display (180 degrees rotation)
    myservo.attach(9);   // attaches the servo on pin 9 to the Servo object
}

void loop(void)
{
    val = analogRead(potpin);        // reads the value of the potentiometer (value between 0 and 1023)
    val = map(val, 0, 1023, 0, 180); // scale it for use with the servo (value between 0 and 180)

    // Check if the potentiometer value has changed
    if (val != prevVal)
    {
        myservo.write(val); // sets the servo position according to the scaled value

        u8x8.setFont(u8x8_font_px437wyse700a_2x2_r); // Set a 2x2 font size
        u8x8.clearDisplay();                         // Clear the screen to avoid overlapping text

        // Centering "Hello" horizontally and vertically
        u8x8.setCursor(2, 2); // Adjust the cursor for the first line
        u8x8.print(val);

        delay(15); // Wait for the servo to get there

        prevVal = val; // Update the previous value
    }

    // You can optionally adjust the delay after potentiometer input detection
    delay(10); // Small delay to avoid excessive CPU usage
}