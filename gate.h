/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gate.h
 * Author: szc
 *
 * Created on November 13, 2015, 7:19 PM
 */

#ifndef GATE_H
#define GATE_H

#include <string>

using namespace std;

class Gate {
public:
    /* Keeps total numbers of gates, inputs and outputs in static integers. */
    static uint cnt_gates, cnt_inputs, cnt_outputs;

    /* Name of the gate as in the input file and its type */
    string name, type;
    
    /* Line number of the gate in the input file */
    uint no;
    
    /* Keeps number of fanout of this gate */
    uint cnt_fout;
    //vector<Gate> gates_fout, gates_fin;

    /* Shows if the gate is primary input or output */
    bool isInput, isOutput;
    
    Gate();
    Gate(const Gate& orig);
    virtual ~Gate();
    
    /*  */
    /*bool operator==(const Gate &gate) const {
        return (name == gate.name);
    }*/
    
    //Gate createInput(string);
    //Gate createOutput(string);
    //void createGate(string);
    
    /*vector<Gate> getFanout();
    vector<Gate> getFanin();
    void addFanout(Gate g);
    void addFanin(Gate g);
    void removeFanout(Gate g);
    void removeFanin(Gate g);*/
};

#endif /* GATE_H */

