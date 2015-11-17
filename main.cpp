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
//#include <vector>
#include <unordered_map>

#include "gate.h"
#include "helper.h"
//#include "hash.h"

using namespace std;

// Initialization of the static members
uint Gate::cnt_gates = 0;
uint Gate::cnt_inputs = 0;
uint Gate::cnt_outputs = 0;

const string str_in = "INPUT(";
const string str_out = "OUTPUT(";

//vector<Gate> gates;
std::unordered_map<std::string, Gate> gateMap;

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

vector<string> splitter;

void process(string s) {
    //cout << "Process" << endl;
    // Check if it is an input or output
    if (s.find(str_in) == 0) {
        Gate g = createInput(s);
        if (gateMap.insert({g.name, g}).second) {
            gateMap[g.name].isInput = true;
        } else {
            gateMap[g.name] = g;
        }
    } else if (s.find(str_out) == 0) {
        Gate g = createOutput(s);
        if (gateMap.insert({g.name, g}).second) {
            gateMap[g.name].isOutput = true;
        } else {
            gateMap[g.name] = g;
        }
    } else {
        splitter = split(s, '=');
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
    cout << ss[1]/*extract(removeSpaces(s))*/ << endl;
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
