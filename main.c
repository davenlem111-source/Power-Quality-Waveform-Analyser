#include <stdio.h>    //This includes the print function
#include <stdlib.h>   //This includes the malloc and free function
#include "IO.h"       //Then this brings all the necessary data and functions from IO.h

int main(void){
    //This allocates memory for 1000 dataset records
    Dataset *data = malloc(MAX_SAMPLES * sizeof(Dataset));

    //This checks if the memory allocation failed
    if (data ==NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    //This then loads the data from my CSV file into the allocated array
    int samplesRead = LoadCSV("power_quality_log.csv", data);

    //This ensures all samples read are valid
    if (samplesRead ==0){
        printf("No samples were read from the CSV file.\n");
        free(data);  //frees the memory to prevent memory leak
        return 1;
    }

    //Now Display number of samples read
    printf("Samples read: %d\n", samplesRead);

    //This processes the data and creates the result.txt
    WriteReport(data, samplesRead);

    //Now free memory again
    free(data);

    //Confirm the program is completed successfully and end the program.
    printf("Analysis complete. Results written to results.txt\n");

    return 0;
}

