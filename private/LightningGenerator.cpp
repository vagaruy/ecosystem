#include <LightningGenerator.h>

LightningGenerator::LightningGenerator() :
        m_random_engine(m_random_device()),
        m_intensity_distribution(5, 255), //// 0-5 is almost invisible so start at a little higher
        m_on_time_distribution(10.0, 200.0), ///values are taken from actual parameters
        m_off_time_distribution(3.0, 100.0) ///values are taken from actual parameters
{
    ;;
}

LightningValue LightningGenerator::generateLightningValue()
{
    LightningValue value;
    value.intensity = m_intensity_distribution(m_random_engine);
    value.total_duration_off = m_off_time_distribution(m_random_engine);
    value.total_duration_on = m_on_time_distribution(m_random_engine);
    return value;
}
