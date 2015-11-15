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

string Gate::getName() { return name; }

int Gate::getNo() { return no; }

void Gate::setName(string s) { name = s; }

void Gate::setNo(int i) { no = i; }

void Gate::createGate(string s) {
    
}