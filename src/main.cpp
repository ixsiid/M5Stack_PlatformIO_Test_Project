#include <Arduino.h>
#include <M5Stack.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>


void displaySensorDetails(void);
void configureSensor(void);

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup()
{
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setCursor(10, 10, 4);
  M5.Lcd.println("Adafruit TSL2561");

  Serial.begin(76800);

  if (!tsl.begin())
  {
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while (1)
      ;
  }

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Setup the sensor gain and integration time */
  configureSensor();
}

void loop()
{
  // put your main code here, to run repeatedly:

  /* Get a new sensor event */
  sensors_event_t event;
  tsl.getEvent(&event);

  /* Display the results (light is measured in lux) */
  if (event.light)
  {
    M5.Lcd.setCursor(20, 50);
    M5.Lcd.print(event.light);
    M5.Lcd.println(" lux        ");
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    M5.Lcd.setCursor(20, 50);
    M5.Lcd.println("Sensor overload");
  }
  delay(250);
}

void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Driver Ver:   ");
  Serial.println(sensor.version);
  Serial.print("Unique ID:    ");
  Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    ");
  Serial.print(sensor.max_value);
  Serial.println(" lux");
  Serial.print("Min Value:    ");
  Serial.print(sensor.min_value);
  Serial.println(" lux");
  Serial.print("Resolution:   ");
  Serial.print(sensor.resolution);
  Serial.println(" lux");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void configureSensor(void)
{
  tsl.enableAutoRange(true);                            /* Auto-gain ... switches automatically between 1x and 16x */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); /* fast but low resolution */
  Serial.println("------------------------------------");
  Serial.print("Gain:         ");
  Serial.println("Auto");
  Serial.print("Timing:       ");
  Serial.println("13 ms");
  Serial.println("------------------------------------");
}
