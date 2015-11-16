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
#define TEST true

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "gate.h"
#include <vector>
#include "helper.h"

using namespace std;

// Initialization of the static members
int Gate::cnt_gates = 0;
int Gate::cnt_inputs = 0;
int Gate::cnt_outputs = 0;

const string str_in = "INPUT(";
const string str_out = "OUTPUT(";

vector<Gate> gates;

void process(string s) {
    // Check if it is an input
    if (s.find(str_in) == 0) {
        Gate toUse = createInput(s);
    } else if (s.find(str_out)) {
        Gate toUse = createOutput(s);
    } else {
        
    }
}

void test() {
    string s = "INPUT(G1gat)";
    //cout << "text" << xxx << endl;
    cout << extract(s) << endl;
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
        }
        
        string line;
        
        // Read the file line by line
        while (getline(infile, line)) {
            
            // Check if the line is a comment or empty.
            // Safest way to do is removing leading spaces but
            // it is assumed that all of the commented lines start with #
            if ((line[0] == '#')||(line.empty())) {
                continue;
            }
            process(removeSpaces(line));
        }
        
        if (infile.bad()) { 
            perror("Error while reading the input file!");
        }
    }
    
#endif
    
    return 0;
}
