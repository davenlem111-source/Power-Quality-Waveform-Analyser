//
// Created by ed2-nlemchi on 03/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"

int testsPassed = 0;  //Counters so i can track how many tests pass or fail
int testsFailed = 0;

// Checks if two integer values match exactly
void checkInt(const char *testName, int actual, int expected) {
    if (actual == expected) {
        printf("[PASSED] %s\n", testName);
        testsPassed++;
    } else {
        printf("[FAILED] %s | Expected: %d, Got: %d\n", testName, expected, actual);
        testsFailed++;
    }
}


//This Checks if an output file was created successfully
void checkFileExists(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        printf("[PASSED] results.txt was created\n");
        testsPassed++;
        fclose(file);
    } else {
        printf("[FAILED] results.txt was not created\n");
        testsFailed++;
    }
}

//This looks for an expected test in an output file
void checkTextInFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("[FAILED] Could not open %s\n", filename);
        testsFailed++;
        return;
    }

    char line[256];
    int found = 0;

    //This reads through the whole file until the text is found
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, text) != NULL) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("[PASSED] Found text: %s\n", text);
        testsPassed++;
    } else {
        printf("[FAILED] Missing text: %s\n", text);
        testsFailed++;
    }
}

int main(void) {
    //This allocates memory for the dataset
    Dataset *data = malloc(MAX_SAMPLES * sizeof(Dataset));

    if (data == NULL) {
        printf("[FAILED] Memory allocation failed\n");
        return 1;
    }

    //This loads the real CSV file
    int samplesRead = LoadCSV("power_quality_log.csv", data);

    //checks the expected number of samples
    checkInt("LoadCSV reads 1000 samples", samplesRead, 1000);

    //This creates the output report
    WriteReport(data, samplesRead);

    //This checks that the report file exists
    checkFileExists("results.txt");

    //Then this checks that the report sections and metrics exist
    checkTextInFile("results.txt", "Phase A");
    checkTextInFile("results.txt", "Phase B");
    checkTextInFile("results.txt", "Phase C");
    checkTextInFile("results.txt", "RMS Voltage");
    checkTextInFile("results.txt", "DC Offset");
    checkTextInFile("results.txt", "Clipping Events");
    checkTextInFile("results.txt", "Average Frequency");
    checkTextInFile("results.txt", "Average Power Factor");
    checkTextInFile("results.txt", "Average THD");

    free(data);  //Now we free the memory after testing

    //Now we print the final integration summary
    printf("\nIntegration Test Summary:\n");
    printf("Passed: %d\n", testsPassed);
    printf("Failed: %d\n", testsFailed);

    return testsFailed;
}
