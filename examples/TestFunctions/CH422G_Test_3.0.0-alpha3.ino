/**
 *  ESP_IOExpander_CH422G working with arduino-esp3 3.0.0-alpha3 release 
 *  https://github.com/espressif/arduino-esp32/releases/tag/3.0.0-alpha3
**/

#include <Arduino.h>
#include <ESP_IOExpander_Library.h>
#include <unistd.h>

#define TP_RST 1
#define LCD_BL 2
#define LCD_RST 3
#define SD_CS 4
#define USB_SEL 5

#define I2C_MASTER_NUM 1
#define I2C_MASTER_SDA_IO 8
#define I2C_MASTER_SCL_IO 9

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */

    /**
     * These development boards require the use of an IO expander to configure the screen,
     * so it needs to be initialized in advance and registered with the panel for use.
     *
     */
    Serial.println("Initialize IO expander");
    /* Initialize IO expander */
    ESP_IOExpander *expander = new ESP_IOExpander_CH422G((i2c_port_t)I2C_MASTER_NUM, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS_000, I2C_MASTER_SCL_IO, I2C_MASTER_SDA_IO);
    expander->init();
    expander->begin();
    expander->multiPinMode(TP_RST | LCD_BL | LCD_RST | SD_CS | USB_SEL, OUTPUT);

    // Set high state on OUTPUT GPIOs
    expander->multiDigitalWrite(TP_RST | LCD_BL | LCD_RST | SD_CS, HIGH);

    // Turn off backlight
    //expander->digitalWrite(USB_SEL, LOW);

    Serial.println("Setup done");
}

void loop()
{
    //Serial.println("Loop");
    sleep(1);
}
