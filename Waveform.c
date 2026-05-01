//
// Created by ed2-nlemchi on 23/04/2026.
//
#include <math.h>  //This is to add extra math functions like the square root function and fab
#include "Waveform.h" //I'm using this to add my header files in here .to help with the linking

#define CLIP_LIMIT 324.9 //define can be used to set a constant value, and im using this to represent the clipping threshold limit

//RMS Calculation
double calculateRMS(double values[], int n){
    double sum =0;  //This stores the total sum
    for (int i = 0; i < n; i ++){
        sum += values[i] * values[i];  //square each sample and then add together
    }
    return sqrt(sum/n);  // calculates the mean of the squares and then square root it
}
//DC offset Calculation
double calculateMean(double values[], int n){
    double sum =0;  //stores the total sum
    for (int i = 0; i < n; i ++){
        sum += values[i];  //adds them together
    }
    return sum/n;  // returns the average value
}
//Calculation of the peak to peak amplitude
void peak_peak(double values[], int n, double *max, double *min){
    *max = values[0];  //This initializes the max with the first value
    *min = values[0];  //This initializes the min with the first value

    for (int i = 1; i < n; i++){
        if(values[i] > *max) *max = values[i];  //updates the max after checking each value and stores the final max
        if(values[i] < *min) *min = values[i];  //updates the min after checking each value and stores the final min
    }
}
//This Detects clipping and computes it
int count_clipping(double values[], int n){
    int count = 0;  //This is a counter for clipped samples
    for(int i = 0; i < n; i ++){
        if(fabs(values[i]) >= CLIP_LIMIT){   //This checks both the positive and negative limits
            count++;  //Starts incrementing if clipping is detected meaning it adds all the clipped samples
        }
    }
    return count;  //Returns the total clipped samples
}
