/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gate.cpp
 * Author: canxx010
 * 
 * Created on November 12, 2015, 3:06 PM
 */

#include "gate.h"

Gate::Gate() { }

Gate::Gate(const Gate& orig) { }

Gate::~Gate() { }

void Gate::createGate(string s) {
    
}

Gate createInput(string s) {
    // Create a gate and adjust its variables
    Gate g;
    g.isInput = true;
    g.isOutput = false;
    g.name = extract(s);
    g.no = Gate::cnt_gates;

    // Increment counters
    Gate::cnt_gates++;
    Gate::cnt_inputs++;
}

Gate createOutput(string s) {
    Gate g;
    g.isInput = false;
    g.isOutput = true;
    g.name = extract(s);
    g.no = Gate::cnt_gates;

    // Increment counters
    Gate::cnt_gates++;
    Gate::cnt_outputs++;
}
