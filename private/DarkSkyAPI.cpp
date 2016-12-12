#include <iostream>
#include "DarkSkyAPI.h"
#include "curl/curl.h"
#include "json/json.h"

std::string *DarkSkyAPI::DownloadedResponse;

DarkSkyAPI::DarkSkyAPI(std::string latitude, std::string longitude) :
        m_latitude(latitude),
        m_longitude(longitude)
{

}

std::string DarkSkyAPI::RequestFormer(std::string &request_url)
{
    CURL *m_curl_library;
    m_curl_library = curl_easy_init();

    struct curl_slist *slist = NULL;
    using namespace darksky_defaults;
    slist = curl_slist_append(slist, "Accept: application/json");
    curl_slist_append(slist, CURL_JSON_TYPE.c_str());
    curl_slist_append(slist, "charsets: utf-8");

    curl_easy_setopt(m_curl_library, CURLOPT_URL, request_url.c_str());
    curl_easy_setopt(m_curl_library, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(m_curl_library, CURLOPT_USERAGENT, "curl/7.38.0");
    curl_easy_setopt(m_curl_library, CURLOPT_HTTPHEADER, slist);
    curl_easy_setopt(m_curl_library, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(m_curl_library, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(m_curl_library, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(m_curl_library, CURLOPT_WRITEFUNCTION, writer);

    int return_status = curl_easy_perform(m_curl_library);

    slist = NULL;

    if (return_status == CURLE_OK)
    {
        char *ct;
        return_status = curl_easy_getinfo(m_curl_library, CURLINFO_CONTENT_TYPE, &ct);
        curl_easy_cleanup(m_curl_library);
        m_curl_library = NULL;
        curl_slist_free_all(slist);
        if ((CURLE_OK == return_status) && ct)
        {
            return *DownloadedResponse;
        }
    }
    curl_easy_cleanup(m_curl_library);
    m_curl_library = NULL;
    curl_slist_free_all(slist);
    return std::string();
}

int DarkSkyAPI::writer(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{

    // Is there anything in the buffer?
    if (buffer_in != NULL)
    {
        // Append the data to the buffer
        //buffer_in->append(data,  nmemb);

        // How much did we write?
        DownloadedResponse = new std::string(data);

        return size * nmemb;
    }

    return 0;
}

WeatherData DarkSkyAPI::requestCurrentWeather()
{
    using namespace darksky_defaults;

    std::string REQUEST_URL = DARKSKY_URL + DARKSKY_SECRET_KEY +
                              KEY_HEADER + m_latitude + "," + m_longitude +
                              "?" + EXCLUSION_LIST;

    std::cout << "Request URL is " << REQUEST_URL << std::endl;

    std::string weather_data = RequestFormer(REQUEST_URL);

    ///Parse in json
    Json::Reader json_reader;
    Json::Value weather_json;
    bool parsedSuccess = json_reader.parse(weather_data, weather_json, false);

    if (!parsedSuccess)
    {
        std::cout << "Illegal json values found \n";
        return WeatherData();
    }

    auto daily_data = weather_json["currently"];

    WeatherData current_weather;
    current_weather.actual_temperature = daily_data["temperature"].asDouble();
    current_weather.apparent_temperature = daily_data["apparentTemperature"].asDouble();
    current_weather.cloudcover = daily_data["cloudCover"].asDouble();
    current_weather.humidity = daily_data["humidity"].asDouble();
    current_weather.precipitaiton_intensity = daily_data["precipIntensity"].asDouble();
    current_weather.precipitation_probability = daily_data["precipProbability"].asDouble();
    current_weather.summary = daily_data["icon"].asString();
    current_weather.windspeed = daily_data["windSpeed"].asDouble();

    auto sun_times = getSunriseAndSunsetTimes(weather_data);
    current_weather.sunrise_time = sun_times.first;
    current_weather.sunset_time = sun_times.second;
    current_weather.lunar_phase = getLunarPhaseForToday(weather_data);

    std::cout << "The current weather details are ActualTemp:" << current_weather.actual_temperature
              << "FeelTemp:" << current_weather.apparent_temperature << "CloudCover:" << current_weather.cloudcover
              << "Humidity:" << current_weather.humidity << "Precip Intensity:"
              << current_weather.precipitaiton_intensity << "Precip Probability:"
              << current_weather.precipitation_probability << "Summary:" << current_weather.summary
              << "Windspeed:" << current_weather.windspeed << "Sunrise Time is:" << current_weather.sunrise_time
              << "Sunset TIme is:" << current_weather.sunset_time
              << "Lunar Phase is:" << current_weather.lunar_phase << std::endl;

    return current_weather;
}

double DarkSkyAPI::getLunarPhaseForToday(std::string &weather_data)
{
    using namespace darksky_defaults;

    ///Parse in json
    Json::Reader json_reader;
    Json::Value weather_json;
    bool parsedSuccess = json_reader.parse(weather_data, weather_json, false);

    if (!parsedSuccess)
    {
        std::cout << "Illegal json values found \n";
        return 0.0;
    }

    auto daily_data = weather_json["daily"]["data"];

    ///Only interested in the first value
    auto it = daily_data.begin();

    double moon_phase = (*it)["moonPhase"].asDouble();

    std::cout << "The moon phase for the day is " << moon_phase << std::endl;

    return moon_phase;
}

std::pair<long, long> DarkSkyAPI::getSunriseAndSunsetTimes(std::string &weather_data)
{
    using namespace darksky_defaults;

    ///Parse in json
    Json::Reader json_reader;
    Json::Value weather_json;
    bool parsedSuccess = json_reader.parse(weather_data, weather_json, false);

    if (!parsedSuccess)
    {
        std::cout << "Illegal json values found \n";
        return std::make_pair<long, long>(0, 0);
    }

    auto daily_data = weather_json["daily"]["data"];

    ///Only interested in the first value
    auto it = daily_data.begin();

    long sunrise_time = (*it)["sunriseTime"].asUInt64();
    long sunset_time = (*it)["sunsetTime"].asUInt64();

    std::cout << "Sunrise Time is:" << sunrise_time
              << "Sunset TIme is:" << sunset_time << std::endl;

    return std::make_pair(sunrise_time, sunset_time);
}