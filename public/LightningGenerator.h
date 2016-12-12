#ifndef ECOSYSTEM_LIGHTNINGGENERATOR_H
#define ECOSYSTEM_LIGHTNINGGENERATOR_H

#include <stdint.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <random>

struct LightningValue
{
    uint16_t intensity;
    double total_duration_on;
    double total_duration_off;
};

///\Class to generate random LED intensity and duration values that can be fed to a LED for simulating lightning
/*
                                    Representative	Range
Stepped Leader
Length of Step	                    50 m	        3 - 200 m
Time interval between steps	        50 uSec	        30 - 125 uSec
Velocity of Propagation	            2000 km/sec	    1000 - 21,000 km/sec
Charge deposited on dart-leader channel	1 C	        0.2 - 6 C
Velocity of propagation	            80,000 km/sec	20,000 - 160,000 km/sec
Current rate of increase	        10 kA/uSec	    <1 - >80 kA/uSec
Time to peak current	            2 uSec	        <1 - 30 uSec
Peak Current	                    10-20 kA	    -110 kA
Time to half of peak current	    40 uSec	        10-250 uSec
Charge transferred                  2.5 C	        0.2 - 20 C
Channel Length	                    5 km	        2 - 14 km
Energy dissipated	                100 kJ/meter
Lightning Flash
Number of strokes per flash	        3-4	            1 - 26
Time interval between strokes	    40 msec	        3 - 100 mSec
Time duration of flash	            0.2 sec	        0.01 0 2 sec
Charge transferred current	        25 C	3 - 90 C
*/

class LightningGenerator
{
public:
    ///\Constructor
    LightningGenerator();

    ///\Function to generate a randomised lightning value. Each flash should call this function and get a
    LightningValue generateLightningValue();

private:

    std::random_device m_random_device;
    std::mt19937 m_random_engine;

    std::uniform_int_distribution<uint16_t> m_intensity_distribution;
    std::uniform_real_distribution<double> m_on_time_distribution;
    std::uniform_real_distribution<double> m_off_time_distribution;
};


#endif //ECOSYSTEM_LIGHTNINGGENERATOR_H
