//
// Created by ed2-nlemchi on 24/04/2026.
//

#ifndef PROJECT_POWER_QUALITY_WAVEFORM_ANALYSER_IO_H  //This is to prevent repetition
#define PROJECT_POWER_QUALITY_WAVEFORM_ANALYSER_IO_H

#define MAX_SAMPLES 1000  //A constant variable for the maximum number of samples in a dataset

typedef struct{   //This represents one row of the csv file with this meaning
    double timestamp;   //Time of each sample
    double phaseA;      //Instantaneous voltage for Phase A
    double phaseB;      //Phase B voltage
    double phaseC;      //Phase C voltage
    double current;     //Line current magnitude
    double frequency;   //Instantaneous Frequency
    double pwr_Factor;  //Ratio of real to apparent power
    double thd;         //Total Harmonic Distortion percentage
} Dataset;

int LoadCSV(const char *filename, Dataset  *data);
//This reads the csv file and stores data in an array of data points
//filename: name of csv file, data: is the array to store values, returns: the number of read samples

void WriteReport(Dataset *data, int n);
//This processes the data and writes the result to an output file, data: the array of samples and n: number
//of samples

#endif //PROJECT_POWER_QUALITY_WAVEFORM_ANALYSER_IO_H
//End of header guard