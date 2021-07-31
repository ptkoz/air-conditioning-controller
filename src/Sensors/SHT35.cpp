#include "Sensors/SHT35.h"

using namespace ACC::Sensors;

void SHT35::initialize() {
    sensor.begin(sensorAddress);
    sensor.heatOff();

    for (double & measure : temperatureMeasures) {
        sensor.read(true);
        measure = sensor.getTemperature();
    }

    for (double & measure : humidityMeasures) {
        sensor.read(true);
        measure = sensor.getHumidity();
    }
}

ACC::Measures::Temperature SHT35::measureTemperature() {
    requestMeasurementFromSensor();

    double sum = 0;
    for (double measure : temperatureMeasures) {
        sum += measure;
    }

    return Measures::Temperature(sum / numberOfMeasures);
}

ACC::Measures::Humidity SHT35::measureHumidity() {
    requestMeasurementFromSensor();

    double sum = 0;
    for (double measure : humidityMeasures) {
        sum += measure;
    }

    return Measures::Humidity(sum / numberOfMeasures);
}

void SHT35::requestMeasurementFromSensor() {
    if (lastSensorRead.getMinAgeSeconds() >= sensorReadInterval) {
        sensor.read(false);

        temperatureMeasures[temperatureMeasureIndex++ % numberOfMeasures] = sensor.getTemperature();
        humidityMeasures[humidityMeasureIndex++ % numberOfMeasures] = sensor.getHumidity();

        lastSensorRead = timeSource.currentTimestamp();
    }
}



