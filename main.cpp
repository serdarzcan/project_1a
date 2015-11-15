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

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "gate.h"
#include <vector>

using namespace std;

/* Initialization of the static members */
int Gate::cnt_gates = 0;
int Gate::cnt_inputs = 0;
int Gate::cnt_outputs = 0;

vector<Gate> gates;

void process(string s) {
    
}

/* Function to remove spaces in a string */
string removeSpaces(string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    return s;
}

/*
 * Main function
 */
int main(int argc, char** argv) {

    /* Check arguments, input file should be provided */
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
            if ((line[0] == "#")||(line.empty())) {
                continue;
            }
            process(removeSpaces(&line));
        }
        
        if (infile.bad()) { 
            perror("Error while reading the input file!");
        }
    }
    
    return 0;
}
