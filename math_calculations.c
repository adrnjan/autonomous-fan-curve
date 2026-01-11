#include <stdio.h>
#include "thermallogic.h"
#include <windows.h>

void calculate_fan_curve(struct readings* state, struct math_variables* settings){
   settings->emaAlpha = 0.1f; //adjust later
   int first_run = 0;
   float base_speed = 0;
   float final_speed = 0;
   state->rawtemp = retrieve_temp_reading();

   if (state->isFirstRun==0){
    first_run = 1;
    state->currentEMA = state->rawtemp;
   }
   else
   state->currentEMA = (settings->emaAlpha * state->rawtemp) + ((1 - settings->emaAlpha) * state->lastEMA);

    //fan_curve base speed (linear, will be placed at 20% between 0 and 40c, will be linear increase 20%-50% from 40c-70c, 75 percent at all times above 70)
    if (state->currentEMA < 40){
        base_speed = 20;
    }
    else if (state->currentEMA > 40 && state->currentEMA < 70){
        base_speed = 20 + (state->currentEMA-40);
    }
    else
    base_speed = 75;

    settings->slope = state->currentEMA - state->lastEMA;
    settings->boost = 0;
    state->lastEMA = state->currentEMA;

    
    if (state->currentEMA>60 && settings->slope > 2.0){
        settings->boost = settings->slope * 1.5;
        //base fan curve + boost factor, or maybe there is a better way to apply the boost
    }

    
    final_speed = base_speed + settings->boost;
        if (final_speed + settings->boost > 100){
        base_speed = 100;
    }
    elseif (final_speed + settings->boost < 0){
        base_speed = 0;

}