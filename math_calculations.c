#include <stdio.h>
#include "thermallogic.h"
#include <windows.h>

void calculate_fan_curve(){
    struct readings state; 
    struct math_variables settings;
    settings.emaAlpha = 0.1f; //adjust later
   int first_run = 0;
   
   while(1){
   state.rawtemp = retrieve_temp_reading();

   if (first_run==0){
    first_run = 1;
    state.currentEMA = state.rawtemp;
   }
   else
   state.currentEMA = (settings.emaAlpha * state.rawtemp) + ((1-settings.emaAlpha) * state.lastEMA);

    //fan_curve base speed (likely will be most confusing part, set by user. needs to be such that there is a balance between sound and perf)

    settings.slope = state.currentEMA - state.lastEMA;
    settings.boost = 0;
    state.lastEMA = state.currentEMA;

    Sleep(1000); 
   }
}