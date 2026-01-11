#include <stdio.h>

struct readings{
    float rawtemp;
    float currentEMA;
    float lastEMA;
    int isFirstRun;
}; 

struct math_variables{
    float emaAlpha;
    float slope;
    float temp_threshold;
    float boost;
};

void calculate_fan_curve(struct readings* state, struct math_variables* settings);