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
//#include <vector>
#include <unordered_map>

#include "gate.h"
#include "helper.h"
//#include "hash.h"

using namespace std;

// Initialization of the static members
uint Gate::cnt_gates = 0; // This will be used in numbering the gates
uint Gate::cnt_inputs = 0;
uint Gate::cnt_outputs = 0;

const string str_in = "INPUT(";
const string str_out = "OUTPUT(";

//vector<Gate> gates;
unordered_map<string, Gate> gateMap;
vector<uint> inp_nos, outp_nos;

Gate createInput(string s) {
    // Create a gate and adjust its variables
    Gate g;
    g.isInput = true;
    //g.isOutput = false;
    g.name = extract(s);
    g.no = Gate::cnt_gates;

    // Increment counters
    Gate::cnt_gates++;
    Gate::cnt_inputs++;
    
    return g;
}

Gate createOutput(string s) {
    Gate g;
    //g.isInput = false;
    g.isOutput = true;
    g.name = extract(s);
    g.no = Gate::cnt_gates;

    // Increment counters
    Gate::cnt_gates++;
    Gate::cnt_outputs++;
    
    return g;
}

struct stats {
    uint count, fanout, fanin;
};

vector<string> splt;
vector<string> inGates;

void process(string s) {
    Gate g;
    // Check if it is an input or output
    
    // Assumption is primary inputs and outputs will be defined first
    // and each gate will be defined once!
    if (s.find(str_in) == 0) {
        g = createInput(s);
        gateMap[g.name] = g;
        
    } else if (s.find(str_out) == 0) {
        g = createOutput(s);
        gateMap[g.name] = g;
        
    } else {
        splt = split(s, '=');
        
        // Check if the gate is already created
        if (gateMap.insert({splt[0], g}).second) {
            // The first time to encounter the gate
            // Update its name
            gateMap[splt[0]].name = splt[0];
        }
        // Update gate info
        gateMap[splt[0]].type = beforePar(splt[1]);
        gateMap[splt[0]].no = Gate::cnt_gates;

        Gate::cnt_gates++;
        
        // Analyze input gates
        inGates = split(extract(splt[1]), ',');
        Gate ig;
        for (auto itr: inGates) {
            if (gateMap.insert({itr, ig}).second) {
                // New gate created
                gateMap[itr].cnt_fout++;
            }
        }
    }
}

void printResults() {
    cout << "Map size: " << gateMap.size() << "\n" << endl;
        
    /*Gate gg;
    bool ok = gateMap.insert({"G1gat", gg}).second;
    cout << "inserting 1 -> \"another one\" " 
          << (ok ? "succeeded" : "failed") << '\n';*/

    for (auto& itr: gateMap) {
        cout << itr.first << " : " << itr.second.isInput << endl;
    }
    cout << "Gate count: " << Gate::cnt_gates << endl;
    cout << "Input count: " << Gate::cnt_inputs << endl;
    cout << "Output count: " << Gate::cnt_outputs << endl;
    //cout << g.isOutput << "\t" << g.isInput << endl;
}

void test() {
    string s = "Gate1=and(G1gat,G2)";
    //cout << "TEST "; << endl;
    vector<string> ss = split(s, '=');
    vector<string> ss2 = split(extract(ss[1]), ',');
    cout << ss2[0] << "    " << ss2[1]/*extract(removeSpaces(s))*/ << endl;
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
        
        printResults();
    }
    
#endif
    
    return 0;
}

/*Gate g1, g2, g3, g4, g5, g6;
    
    g1.isInput = false;
    g1.isOutput = true;
    g1.name = "G22gat";
    
    g2.isInput = false;
    g2.isOutput = true;
    g2.name = "G23gat";
    
    g3.isInput = true;
    g3.isOutput = true;
    g3.name = "G1gat";
    
    g4.isInput = false;
    g4.isOutput = true;
    g4.name = "GG";
    
    g5.isInput = false;
    g5.isOutput = true;
    g5.name = "GGG";
    
    g6.isInput = false;
    g6.isOutput = true;
    g6.name = "G";
    
    std::unordered_map<std::string,Gate*>
              myrecipe,
              mypantry = {{g1.name, &g1},{g2.name, &g2}};

    std::pair<std::string,Gate*> myshopping (g3.name, &g3);

    myrecipe.insert (myshopping);                        // copy insertion
    //myrecipe.insert (std::make_pair<string,Gate>(g4.name, g4)); // move insertion
    myrecipe.insert (mypantry.begin(), mypantry.end());  // range insertion
    myrecipe.insert ( {{g5.name, &g5},{g6.name, &g6}} );    // initializer list insertion

    std::cout << "myrecipe contains:" << std::endl;
    for (auto& x: myrecipe)
      std::cout << x.first << ": " << x.second->name << std::endl;

    std::cout << std::endl;*/