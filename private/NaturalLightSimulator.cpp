#include <DarkSkyAPI.h>
#include <NaturalLightSimulator.h>
#include <chrono>
#include <iostream>

NaturalLightSimulator::NaturalLightSimulator(const WeatherData &m_weather_data)
        : m_weather_data(m_weather_data)
{

}

LedRgbIntensity NaturalLightSimulator::getCurrentNaturalLightLedParams()
{
    // get the current time
    const auto now = std::chrono::system_clock::now();

    // transform the time into a duration since the epoch
    const auto epoch = now.time_since_epoch();

    // cast the duration into seconds
    const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);


    LedRgbIntensity led_data;
    ///Is it before sunrise ?
    if (m_weather_data.sunrise_time > seconds.count())
    {

    }///or after sunset
    else if (m_weather_data.sunset_time < seconds.count())
    {

    }///We are in the day
    else
    {

    }

    // return the number of seconds
    std::cout << "Seconds since epoch is " << seconds.count();


    return LedRgbIntensity();
}

std::tuple<uint8_t, uint8_t, uint8_t> NaturalLightSimulator::getRgbFromColorTemperature(const double &color_temperature)
{
    return std::tuple<uint8_t, uint8_t, uint8_t>();
}
