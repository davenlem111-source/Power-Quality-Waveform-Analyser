//
// Created by ed2-nlemchi on 24/04/2026.
//
#include <stdio.h>      //We are including the file handling functions
#include <stdlib.h>     //This is just for the exit() function not really important but,I prefer this function
#include "IO.h"         //Included the data struct and functions
#include "Waveform.h"   // This brings the waveform functions

static void WritePhaseReport(FILE *file, const char *phaseName, double values[], int n){
    double max, min;   //Firstly the use of static is to ensure it is only accessible in this file, this is done to reduce repetition basically, and then the function itself writes analysis results for one phase either A,B or C

    //This finds the maximum and minimum values using a pointer
    peak_peak(values, n, &max, &min);

    //Then we write the calculated values to the file
    fprintf(file, "%s:\n", phaseName);
    fprintf(file, "RMS Voltage:  %.2f v\n", calculateRMS(values, n));
    fprintf(file, "DC Offset:  %.2f v\n", calculateMean(values, n));
    fprintf(file, "Peak Voltage:  %.2f v\n", max);
    fprintf(file, "Minimum Voltage:  %.2f v\n", min);
    fprintf(file, "Peak-to-Peak Voltage:  %.2f v\n", max - min);
    fprintf(file, "Clipping Events: %d\n\n", count_clipping(values, n));
}
//THE CSV LOADING FUNCTION
//This reads the CSV file and stores data into the dataset array
int LoadCSV(const char *filename, Dataset *data){
    FILE *file = fopen(filename, "r");

    //This just basically checks if the file was opened successfully, it's better to be safe
    if (file == NULL){
        printf("There is an Error opening file: %s\n",filename);
        exit(1);
    }

    //To avoid complications and error this code is done to skipp the header row, that is those column names
    char header[256];
    fgets(header, sizeof(header), file);

    int i = 0;

    //This reads each row and ensures exactly 8 values are read per row
    while (i < MAX_SAMPLES && fscanf(file, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &data[i].timestamp, &data[i].phaseA,&data[i].phaseB,&data[i].phaseC,&data[i].current,&data[i].frequency,&data[i].pwr_Factor,&data[i].thd) == 8){
        i++;
    }
    fclose(file);  //Now close file after reading very important
    return i;          //Return number of samples read
}


//THE REPORT WRITING FUNCTION
//this processes data
void WriteReport(Dataset *data, int n){
    FILE *file = fopen("results.txt", "w"); // and writes results in a result.txt file

    //checks if the output file opened successfully
    if (file == NULL) {
        printf("Error creating results.txt\n");
        exit(1);
    }

    //Now we create an array to store each phase separately
    double A[MAX_SAMPLES];
    double B[MAX_SAMPLES];
    double C[MAX_SAMPLES];

    //and create variables to calculate averages
    double frequencySum = 0.0;
    double pwr_FactorSum =0.0;
    double thdSum = 0.0;

    //Extracts the values from my struct into arrays
    for (int i =0; i < n; i++){
        A[i] = data[i].phaseA;
        B[i] = data[i].phaseB;
        C[i] = data[i].phaseC;


        //Then this records the total sums
        frequencySum += data[i].frequency;
        pwr_FactorSum += data[i].pwr_Factor;
        thdSum += data[i].thd;
    }

    //Header for my report
    fprintf(file, "POWER QUALITY WAVEFORM ANALYSER REPORT\n\n");
    fprintf(file, "Number of samples analysed: %d\n\n",n);


    //Analysis each phase
    WritePhaseReport(file, "Phase A", A, n);
    WritePhaseReport(file, "Phase B", B, n);
    WritePhaseReport(file, "Phase C", C, n);

    //Then write the overall system values
    fprintf(file, "Overall Measurements: \n");


    //This is done so I can avoid division by zero
    if (n > 0) {
        fprintf(file, "Average Frequency:  %.2f Hz\n", frequencySum/n);
        fprintf(file, "Average Power Factor:  %.2f\n",pwr_FactorSum/n);
        fprintf(file, "Average THD:  %.2f %%\n",thdSum/n);
    } else{
        fprintf(file, "No valid samples found.\n");
    }

    fclose(file);  //Then finally I close the output file.
}

















