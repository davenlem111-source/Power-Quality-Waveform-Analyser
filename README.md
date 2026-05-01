# Power Quality Waveform Analyser

## Author:
David Nlemchi

## Module:
UGMFGT-15-1 Programming for Engineers

## Description
This project is a C-based Power Quality Waveform Analyser designed to process a 3-phase industrial power supply dataset.

The program:
- Reads waveform data from a CSV file
- Calculates RMS voltage
- Calculates DC offset
- Detects clipping events
- Calculates peak and peak-to-peak voltages
- Computes average frequency, power factor, and THD
- Generates a structured report in results.txt

---

# Project Structure

- main.c → Main program entry point
- IO.c / IO.h → File input/output operations
- waveform.c / waveform.h → Signal processing calculations
- CMakeLists.txt → Build configuration

---

# How to Compile (GCC)

```bash
gcc main.c IO.c waveform.c -o analyser -lm
```

---

# How to Run

```bash
./analyser
```

---

# CLion Instructions

1. Open project folder in CLion
2. Ensure all .c and .h files are included
3. Place power_quality_log.csv in the working directory
4. Click Run

---

# GitHub Repository

https://github.com/davenlem111-source/Power-Quality-Waveform-Analyser.git