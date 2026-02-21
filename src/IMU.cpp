#include "IMU.h"
#include "Board.h"
#include "Lpf2/log/log.h"

BNO08x IMU;
void setReports(void);

bool IMU_exists = false;

int IMU_init(TwoWire &wirePort)
{
    if (IMU.begin(0x4A, wirePort, BNO08X_INT, BNO08X_RST) == false)
    {
        LPF2_LOG_E("BNO08x not detected.");
        return 1;
    }
    LPF2_LOG_D("BNO08x found!");
    setReports();
    IMU_exists = true;
    return 0;
}

int IMU_update()
{
    if (!IMU_exists)
    {
        return 1;
    }
    if (IMU.wasReset())
    {
        LPF2_LOG_D("IMU sensor was reset");
        setReports();
    }

    // Has a new event come in on the Sensor Hub Bus?
    if (IMU.getSensorEvent() == true)
    {

        // is it the correct sensor data we want?
        if (IMU.getSensorEventID() == SENSOR_REPORTID_ROTATION_VECTOR)
        {

            float quatI = IMU.getQuatI();
            float quatJ = IMU.getQuatJ();
            float quatK = IMU.getQuatK();
            float quatReal = IMU.getQuatReal();
            float quatRadianAccuracy = IMU.getQuatRadianAccuracy();

            LPF2_LOG_D("Quaternion - I: %.2f, J: %.2f, K: %.2f, Real: %.2f, Accuracy: %.2f",
                       quatI, quatJ, quatK, quatReal, quatRadianAccuracy);
        }
        if (IMU.getSensorEventID() == SENSOR_REPORTID_ACCELEROMETER)
        {
            float x = IMU.getAccelX();
            float y = IMU.getAccelY();
            float z = IMU.getAccelZ();

            LPF2_LOG_D("Accelerometer - X: %.2f, Y: %.2f, Z: %.2f", x, y, z);
        }
        if (IMU.getSensorEventID() == SENSOR_REPORTID_GYROSCOPE_CALIBRATED) {
            float x = IMU.getGyroX();
            float y = IMU.getGyroY();
            float z = IMU.getGyroZ();

            LPF2_LOG_D("Gyroscope - X: %.2f, Y: %.2f, Z: %.2f", x, y, z);
        }
    }
    return 0;
}

// Here is where you define the sensor outputs you want to receive
void setReports(void)
{
    LPF2_LOG_D("Setting desired reports");
    // if (IMU.enableRotationVector() == true)
    // {
    //     LPF2_LOG_D("Rotation vector enabled");
    //     LPF2_LOG_D("Output in form i, j, k, real, accuracy");
    // }
    // else
    // {
    //     LPF2_LOG_E("Could not enable rotation vector");
    // }
    // if (IMU.enableAccelerometer() == true)
    // {
    //     LPF2_LOG_D("Accelerometer enabled");
    //     LPF2_LOG_D("Output in form x, y, z, in m/s^2");
    // }
    // else
    // {
    //     LPF2_LOG_E("Could not enable accelerometer");
    // }
    // if (IMU.enableGyro() == true)
    // {
    //     LPF2_LOG_D("Gyro enabled");
    //     LPF2_LOG_D("Output in form x, y, z, in radians per second");
    // }
    // else
    // {
    //     LPF2_LOG_E("Could not enable gyro");
    // }
}