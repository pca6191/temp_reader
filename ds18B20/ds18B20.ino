
/*
 * @file  使用 2 顆 DS18B20, 接在 D2 pin，定期更新溫度讀值 (ex. 1 sec) 到 RS232.
 */
#include "Timer.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_1 2

OneWire oneWire_in(ONE_WIRE_BUS_1);

DallasTemperature sensors_on_bus(&oneWire_in);

Timer t;

void setup(void)
{
    Serial.begin(9600);
    Serial.println("show temperature of two DS18B20.");

    sensors_on_bus.begin(); //init the temperature reading object.

    t.every(1000, periodRouting); //set periodic callback function
}

void loop(void)
{
  t.update(); //update internal tick of timer
}

//callback function in period to do somthing
void periodRouting()
{
    sensors_on_bus.requestTemperatures();   //have all the sensors on the bus update the temperature
    Serial.print(sensors_on_bus.getTempCByIndex(0)); //get temp. of the first sensor
    Serial.print(" , ");
    Serial.print(sensors_on_bus.getTempCByIndex(1)); //get temp. of the second sensor
    Serial.println("");
}

