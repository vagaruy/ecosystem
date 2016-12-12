#ifndef ECOSYSTEM_NATURALLIGHTSIMULATOR_H
#define ECOSYSTEM_NATURALLIGHTSIMULATOR_H

#include "DarkSkyAPI.h"

struct LedRgbIntensity
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t intensity;
};

///\Class that replicates the natural light at different times of the day based on current sunrise and sunset and moon phase
///and cloud cover and storm conditions
class NaturalLightSimulator
{
public:

    ///\Constructor that takes in the weather data.
    explicit NaturalLightSimulator(const WeatherData &m_weather_data);

    ///Get the current RGB and intensity values
    LedRgbIntensity getCurrentNaturalLightLedParams();

private:

    std::tuple<uint8_t ,uint8_t ,uint8_t > getRgbFromColorTemperature(const double& color_temperature);

    WeatherData m_weather_data;


};

#endif //ECOSYSTEM_NATURALLIGHTSIMULATOR_H
