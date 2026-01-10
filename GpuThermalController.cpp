#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include "nvapi.h"
#include <filesystem>

const float EMA_ALPHA = 0.2f;           
const float DERIVATIVE_GAIN = 5.0f;      
const float MIN_TEMP_FOR_BOOST = 60.0f;  
const float MIN_SLOPE_FOR_BOOST = 1.0f;  

const std::string FILE_EMA = "C:\\SensorData\\gpu_ema.sensor";
const std::string FILE_BOOST = "C:\\SensorData\\gpu_derivative.sensor";