#include <iostream>
#include <thread>
#include "LightningGenerator.h"

int main()
{
    std::cout << "Random Lightning Value Generator" << std::endl;
    LightningGenerator random_lightning_generator;

    ///random generators take about 2 microseconds to grab the value.
    while (1)
    {
        auto lightning_value = random_lightning_generator.generateLightningValue();
        std::cout << "Intensity:" << lightning_value.intensity
                  << "ON Time:" << lightning_value.total_duration_on
                  << "OFF Time:" << lightning_value.total_duration_off << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}