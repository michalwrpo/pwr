#include "logger.h"

#include "Arduino.h"
#include "HardwareSerial.h"
#include "string_helper.h"

#include <SD.h>

bool Logger::m_partial_log = false; 
char* Logger::m_filename = nullptr;

static void Logger::init(const char* filename) {
    m_filename = malloc((strlen(filename) + 1) * sizeof(char));
    strcpy(m_filename, filename);
    SD.remove(m_filename);
    File logFile = SD.open(m_filename, FILE_WRITE);
    
    if (!logFile) {
        Serial.print("Failure on opening file ");
        Serial.println(m_filename);
        while (1);
    }

    logFile.close();
    m_partial_log = false;
}

static void Logger::partial_log(const char* msg) {
    File logFile = SD.open(m_filename, FILE_WRITE); 

    if (!m_partial_log) {
        unsigned long t = millis();
        logFile.print(t);
        logFile.print(" - ");
    }

    logFile.print(msg);
    logFile.print(" ");
    logFile.close();
    m_partial_log = true;
}

static void Logger::log(const char *msg) {
    File logFile = SD.open(m_filename, FILE_WRITE);

    if (!m_partial_log) {
        unsigned long t = millis();
        logFile.print(t);
        logFile.print(" - ");
    }

    logFile.print(msg);
    logFile.write("\n");
    logFile.close();
    m_partial_log = false;
}

static void Logger::log(long number) {
    File logFile = SD.open(m_filename, FILE_WRITE);
    if (!m_partial_log) {
        unsigned long t = millis();
        logFile.print(t);
        logFile.print(" - ");
    }

    logFile.print(number);
    logFile.write("\n");
    logFile.close();
    m_partial_log = false;
}

static void Logger::read() {
    File logFile = SD.open(m_filename, FILE_READ);

    Serial.println("Reading logs");
    if (logFile) {
        Serial.println(logFile.available());
        while (logFile.available()) {
            char ch = logFile.read(); 
            Serial.print(ch);
        }
        logFile.close();
    } else {
        Serial.print(F("SD Card: error on opening file "));
        Serial.println(m_filename);
    }
}