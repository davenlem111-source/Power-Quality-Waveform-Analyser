//
// Created by ed2-nlemchi on 03/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"

int testsPassed = 0;
int testsFailed = 0;

void checkInt(const char *testName, int actual, int expected) {
    if (actual == expected) {
        printf("[PASSED] %s\n", testName);
        testsPassed++;
    } else {
        printf("[FAILED] %s | Expected: %d, Got: %d\n", testName, expected, actual);
        testsFailed++;
    }
}

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

void checkTextInFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("[FAILED] Could not open %s\n", filename);
        testsFailed++;
        return;
    }

    char line[256];
    int found = 0;

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
    Dataset *data = malloc(MAX_SAMPLES * sizeof(Dataset));

    if (data == NULL) {
        printf("[FAILED] Memory allocation failed\n");
        return 1;
    }

    int samplesRead = LoadCSV("power_quality_log.csv", data);

    checkInt("LoadCSV reads 1000 samples", samplesRead, 1000);

    WriteReport(data, samplesRead);

    checkFileExists("results.txt");

    checkTextInFile("results.txt", "Phase A");
    checkTextInFile("results.txt", "Phase B");
    checkTextInFile("results.txt", "Phase C");
    checkTextInFile("results.txt", "RMS Voltage");
    checkTextInFile("results.txt", "DC Offset");
    checkTextInFile("results.txt", "Clipping Events");
    checkTextInFile("results.txt", "Average Frequency");
    checkTextInFile("results.txt", "Average Power Factor");
    checkTextInFile("results.txt", "Average THD");

    free(data);

    printf("\nIntegration Test Summary:\n");
    printf("Passed: %d\n", testsPassed);
    printf("Failed: %d\n", testsFailed);

    return testsFailed;
}
