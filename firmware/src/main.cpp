
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#include "RFIDReader.h"
#include "driver/led.h"
#include "utils/timer.h"
#include "utils/combination.h"

RFIDReader rfidReader(10, 19);
driver::led succes_led(2);
LiquidCrystal lcd(8, 3, 4, 5, 6, 7);
combination puzzle_comb;

int current_id = 0;  // The ID that is currently being checked against
int previous_id = 0; // The ID that was previously checked against

enum card_types
{
    C1 = 30,
    C2 = 158,
    C3 = 206,
    C4 = 77,
    C5 = 221,
    C6 = 29,
    PHONE_NOET = 8
};

// Define the custom character for the LCD
byte square_char[8] = {
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b01110,
};

void setup()
{
    current_id = 0;
    previous_id = 0;
    Serial.begin(9600);
    rfidReader.begin();

    Serial.println("Init done");
    lcd.begin(16, 2);
    lcd.createChar(0, square_char);
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Enter Formula:");
    delay(1000);

}



void printCard()
{
    lcd.clear();
    lcd.setCursor(0, 0);

    String progress = "Progress:";
    for (int i = 0; i < puzzle_comb.get_id_index(); i++) {
        progress += String((char) square_char[i]);
    }
    lcd.print(progress);
    lcd.setCursor(0, 1);

    switch (current_id)
    {
    case C1:
        lcd.print("Control Rods");
        break;
    case C2:
        lcd.print("Neutron Control");
        break;
    case C3:
        lcd.print("Uranium Fuel");
        break;
    case C4:
        lcd.print("Neutron Flux");
        break;
    case C5:
        lcd.print("Heat Transfer");
        break;
    case C6:
        lcd.print("Power Gen");
        break;
    case PHONE_NOET:
        lcd.print("Telefoon noet");
        break;
    default:
        lcd.print("Insert Material");
        lcd.setCursor(0, 1);
        break;
    }
    lcd.setCursor(0, 1);
}

void loop()
{
    if (rfidReader.read())
    {
        previous_id = current_id;
        current_id = rfidReader.get_id(0);

        // If the card ID has changed, update the last card read time
        if (current_id != previous_id)
        {
            Serial.write(current_id);
            puzzle_comb.add(current_id);
            
            printCard();
            if (puzzle_comb.is_correct())
            {
                delay(1000);
                Serial.write("Correct Combination");
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.write("Success!");
                lcd.setCursor(0,1);
                lcd.write("1234");
                delay(4000);
                puzzle_comb.reset();
                setup();

            } else if (puzzle_comb.get_id_index() == 6) {
                delay(1000);
                Serial.write("Incorrect Combination");
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.write("Incorrect");
                delay(4000);
                puzzle_comb.reset();
                setup();
            }
        }
    }
}