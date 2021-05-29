/**
 * \file main.cpp
 * \brief Lectura de Temperatura [°C] y Humedad Relativa [%] sensor SHT30
 * \author Joseph Santiago Portilla Martínez - Karen Stefania Mirama Eraso
 */ 
#include <Arduino.h>
#include <Wire.h>
#include "SHT3X.hpp"

// ------------ DEFINICION DE CONSTANTES------------
// Definicion de Pines I2C
const uint8_t SCL_PIN = 12;
const uint8_t SDA_PIN = 14;
// Definicion de tiempos
const uint16_t TMedicion = 2000;

// ------------ DEFINICION DE VARIABLES------------
unsigned long tActual = 0; // Tiempo actual de millis()
unsigned long tPrevio = 0; // Tiempo previo de Medición

void setup(){
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
}

void loop(){
    float temp, rh, tTol, rhTol;

    tActual = millis(); 

    if (tActual > tPrevio + TMedicion) {     
        readData(temp, rh); // Lectura de datos de Temperatura y Humedad Relativa SHT30
        rhTolerance(rh, rhTol, 0); // Obtener Tolerancia de Humedad Relativa SHT30
        tempTolerance(temp, tTol, 0); // Obtener Tolerancia de Temperatura SHT30
        
        Serial.print("Temperatura [°C]: ");
        Serial.print(temp);
        Serial.print(" ± ");
        Serial.println(tTol);
        Serial.print("Humedad Relativa [%]: ");
        Serial.print(rh);
        Serial.print(" ± ");
        Serial.println(rhTol);

        tPrevio = tActual;
    }
}