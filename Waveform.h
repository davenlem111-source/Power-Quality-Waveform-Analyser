//
// Created by ed2-nlemchi on 23/04/2026.
//

#ifndef PROJECT_POWER_QUALITY_WAVEFORM_ANALYSER_WAVEFORM_H   //If WAVEFORM_H is not defined
#define PROJECT_POWER_QUALITY_WAVEFORM_ANALYSER_WAVEFORM_H   //Define it, that's what it simply means

double calculateRMS(double values[], int n); //This calculates the RMS value of the waveform, values[]: is the array of the voltage samples and, n: is the number of samples
double calculateMean(double values[], int n);//This calculates the mean value of the waveform which can be used to detect the DC Offset
void peak_peak(double values[], int n, double *max,double *min);
int count_clipping(double values[], int n);

#endif //PROJECT_POWER_QUALITY_WAVEFORM_ANALYSER_WAVEFORM_H
