#include <iostream>
#include <thread>
#include <DarkSkyAPI.h>
#include <NaturalLightSimulator.h>

int main()
{
    std::cout << "Weather Data Tester" << std::endl;

    //Default to boston weather data
    DarkSkyAPI weather_data;
    //weather_data.requestCurrentWeather();
    WeatherData data;
    NaturalLightSimulator simulator(data);
    simulator.getCurrentNaturalLightLedParams();
    return 0;

}