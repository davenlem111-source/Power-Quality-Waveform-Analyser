//
// Created by ed2-nlemchi on 03/05/2026.
//
#include <stdio.h>
#include <math.h>
#include "Waveform.h"

int testsPassed = 0;  //Counters so i can track how many tests pass or fail
int testsFailed = 0;

//This checks if the 2 double values are close enough to be considered equal
void checkDouble(const char *testName, double actual, double expected) {
    if (fabs(actual - expected) < 0.01) {
        printf("[PASSED] %s\n", testName);
        testsPassed++;
    } else {
        printf("[FAILED] %s | Expected: %.2f, Got: %.2f\n", testName, expected, actual);
        testsFailed++;
    }
}

//While this checks if two integers are exactly equal
void checkInt(const char *testName, int actual, int expected) {
    if (actual == expected) {
        printf("[PASSED] %s\n", testName);
        testsPassed++;
    } else {
        printf("[FAILED] %s | Expected: %d, Got: %d\n", testName, expected, actual);
        testsFailed++;
    }
}

int main(void) {
    //This tests the RMS using simple known values
    double values1[] = {3.0, 4.0};
    checkDouble("calculateRMS simple values", calculateRMS(values1, 2), 3.54);

    //This tests RMS using values that are the same
    double values2[] = {230.0, 230.0, 230.0};
    checkDouble("calculateRMS repeated voltage", calculateRMS(values2, 3), 230.00);

    //These tests mean, using both positive and negative numbers
    double values3[] = {10.0, -10.0, 20.0, -20.0};
    checkDouble("calculateMean balanced waveform", calculateMean(values3, 4), 0.00);

    //Tests mean using only positive numbers
    double values4[] = {5.0, 10.0, 15.0};
    checkDouble("calculateMean positive values", calculateMean(values4, 3), 10.00);

    //Tests the peak and minimum detection
    double values5[] = {-325.0, -100.0, 0.0, 100.0, 325.0};
    double max, min;
    peak_peak(values5, 5, &max, &min);

    checkDouble("peak_peak maximum", max, 325.00);
    checkDouble("peak_peak minimum", min, -325.00);

    //Tests the data with no clipping values
    double values6[] = {100.0, 324.9, -324.9, 200.0};
    checkInt("count_clipping positive and negative", count_clipping(values6, 4), 2);

    double values7[] = {100.0, 200.0, -300.0};
    checkInt("count_clipping no clipping", count_clipping(values7, 3), 0);

    //Then this prints the final unit test summary
    printf("\nUnit Test Summary:\n");
    printf("Passed: %d\n", testsPassed);
    printf("Failed: %d\n", testsFailed);

    return testsFailed;
}
