#include <Wire.h>
#include <AHT20.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
AHT20 aht20;

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

void setup()
{
  Serial.begin(115200);

  // Setup Display
  Serial.println("128x64 OLED FeatherWing test");
  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);

  // Setup Sensor
  Wire.begin(); //Join I2C bus
  //Check if the AHT20 will acknowledge
  if (aht20.begin() == false)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }
  Serial.println("AHT20 acknowledged.");
}

void loop()
{
  //If a new measurement is available
  if (aht20.available() == true)
  {
    //Get the new temperature and humidity value
    double temperature = aht20.getTemperature();
    double humidity = aht20.getHumidity();
    double temp_sensor = temperature;
    double hum_sensor = humidity;

    //Print the results
    //Serial.print("Temperature: ");
    //Serial.print(temperature, 2);
    //Serial.print(" C\t");
    //Serial.print("Humidity: ");
    //Serial.print(humidity, 2);
    Serial.print("% RH");

    Serial.println();

    // text display tests
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.println("Env Data");
    //display.setTextSize(1);
    display.print("Temp:");
    display.println(temperature);
    display.print("Hum:");
    display.print(humidity);
    display.println("%");
    display.display(); // actually display all of the above
    Serial.println("Reached Loop");
  }

  delay(500);
}