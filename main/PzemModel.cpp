//
// Created by wupolung on 2024/5/13.
//
#include "PzemModel.h"
#include <ArduinoJson.h>


PzemModel::PzemModel() {

    Voltage = 0.0f;
    Current = 0.0f;
    Power = 0.0f;
    Energy = 0.0f;
    Frequency = 0.0f;
    PF = 0.0f;
}

String PzemModel::ToJson() {
    StaticJsonDocument<200> doc;

    String output;
    doc["Voltage"] = Voltage;
    doc["Current"] = Current;
    doc["Power"] = Power;
    doc["Energy"] = Energy;
    doc["Frequency"] = Frequency;
    doc["PF"] = PF;

    serializeJson(doc, output);
    return output;
}