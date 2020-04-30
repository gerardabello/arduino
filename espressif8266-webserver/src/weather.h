#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>
#include <DHT.h>

class Weather
{
  private:
    DHT dht;
  public:
    Weather(){
      dht.setup(D7);
    }

    float getTemperature() {
      return dht.getTemperature();
    }

    float getHumidity() {
      return dht.getHumidity();
    }

    String getStatusString() {
      return dht.getStatusString();
    }
};



#endif

