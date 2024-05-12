//
// Created by wupolung on 2024/5/13.
//
#define PZEM_MODEL_H
#define PZEM_MODEL_H

#include <ArduinoJson.h>

class PzemModel {
public:
    PzemModel();

    float Voltage;
    float Current;
    float Power;
    float Energy;
    float Frequency;
    float PF;

    String ToJson();
};