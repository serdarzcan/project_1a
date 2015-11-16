/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: canxx010
 *
 * Created on November 12, 2015, 3:06 PM
 */
#define TEST false

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "gate.h"
#include "helper.h"
#include "hash.h"

using namespace std;

// Initialization of the static members
int Gate::cnt_gates = 0;
int Gate::cnt_inputs = 0;
int Gate::cnt_outputs = 0;

const string str_in = "INPUT(";
const string str_out = "OUTPUT(";

vector<Gate> gates;
unordered_map<string, Gate/*, Hash*/> gateMap;

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
    
    return g;
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
    
    return g;
}

void process(string s) {
    //cout << "Process" << endl;
    // Check if it is an input
    if (s.find(str_in) == 0) {
        Gate g = createInput(s);
        gateMap.insert({g.name, g});
        cout << "Input created: " << endl;
        cout << g.name << " " << g.isInput << " " << g.isOutput << endl;
    } else if (s.find(str_out) == 0) {
        Gate g = createOutput(s);
        gateMap.insert({g.name, g});
        cout << "Output created: " << endl;
        cout << g.name << " " << g.isInput << " " << g.isOutput << endl;
    } else {
        //cout << "Gate created" << endl;
    }
}

/*
 * Main function
 */
int main(int argc, char** argv) {

#if(TEST)
    test();
#else
    // Check arguments, input file should be provided
    if (argc < 2) {
        cout << "Input file is not provided!" << endl;
        exit(0); // Exit the program
    } else {
        ifstream infile;
        infile.open(argv[1]);
        
        // Try to open the input file
        if (!infile.is_open()) { 
            perror("Error while opening the input file!");
        } else {        
            cout << "File opened!" << endl;
        }
        
        string line;
        
        // Read the file line by line
        while (getline(infile, line)) {
            //cout << "While" << endl;
            
            // Check if the line is a comment or empty.
            // Safest way to do is removing leading spaces but
            // it is assumed that all of the commented lines start with #
            if ((line[0] == '#')||(line.empty())) {
                //cout << "Empty or comment" << endl;
                continue;
            }
            process(removeSpaces(line));
        }
        
        if (infile.bad()) { 
            perror("Error while reading the input file!");
        }
        
        cout << "Map size: " << gateMap.size() << endl;
        //Gate g = gateMap["G22gat"];
        
        for (auto &itr: gateMap) {
            cout << itr.first << " : " << itr.second.name << endl;
        }
        cout << "Gate count: " << Gate::cnt_gates << endl;
        cout << "Input count: " << Gate::cnt_inputs << endl;
        cout << "Output count: " << Gate::cnt_outputs << endl;
        //cout << g.isOutput << "\t" << g.isInput << endl;
    }
    
#endif
    
    return 0;
}

void test() {
    string s = "INPUT(G1gat)";
    //cout << "text" << xxx << endl;
    cout << extract(s) << endl;
}