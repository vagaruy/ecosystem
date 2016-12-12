#ifndef ECOSYSTEM_DARKSKYAPI_H
#define ECOSYSTEM_DARKSKYAPI_H

///\Class to communicate with the Dark Sky API to extract the weather data.
/*
Following values are extracted from the DarkSkyAPI
cloudCover
Summary clear-day, clear-night, rain, snow, sleet, wind, fog, cloudy, partly-cloudy-day, or partly-cloudy-night
Moon phase
sunrise time, sunset time,
Precipitation Probability
Precip. Type
visibility
 */

#include <string>
#include <json/value.h>

namespace darksky_defaults
{
const std::string DARKSKY_URL = "https://api.darksky.net/forecast/";
const std::string DARKSKY_SECRET_KEY = "12a80a1b3c7c8cc42ec845a7319bf4a7";

const std::string KEY_HEADER = "/";
const std::string CURL_JSON_TYPE = "Content-Type: application/json";
const std::string EXCLUSION_LIST = "exclude=minutely,hourly,alerts,flags";

}
struct WeatherData
{
    double actual_temperature;
    double apparent_temperature;
    double windspeed;
    double precipitation_probability;
    double precipitaiton_intensity;
    double humidity;
    double cloudcover;
    double sunrise_time;
    double sunset_time;
    double lunar_phase;
    std::string summary;
};

class DarkSkyAPI
{
public:

    ///\Class Constructor Default to Boston
    explicit DarkSkyAPI(std::string latitude = "42.3598965", std::string longitude = "-71.0905594");

    WeatherData requestCurrentWeather();



private:

    double getLunarPhaseForToday(std::string&);

    std::pair<long, long> getSunriseAndSunsetTimes(std::string&);

    std::string RequestFormer(std::string &request_url);

    static std::string *DownloadedResponse;

    static int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in);

    std::string m_latitude;
    std::string m_longitude;

};


#endif //ECOSYSTEM_DARKSKYAPI_H
