#include <vector>
#ifndef GYRO_H_
#define GYRO_H_

void MPU6050_Init();
void i2cScanner();
std::vector<double> getGyroValues();

#endif
