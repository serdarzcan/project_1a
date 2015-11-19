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
#include <unordered_map>

#include "gate.h"
#include "helper.h"

using namespace std;

// Initialization of the static members
uint Gate::cnt_gates = 0; // This will be used in numbering the gates
/*uint Gate::cnt_inputs = 0;
uint Gate::cnt_outputs = 0;*/

const string str_in = "INPUT(";
const string str_out = "OUTPUT(";

uint max_fanout = 0;

// Keeps all of the gates
unordered_map<string, Gate> gateMap;

// Keeps histogram of fanouts
unordered_map<uint, uint> histo;

// Keeps fanin/fanout numbers of gate types
unordered_map<string, Stats> type_stats;

// To keep input/output gate numbers
vector<uint> inp_nos, outp_nos;

Gate createInput(string s) {
    // Create a gate and adjust its variables
    Gate g;
    g.isInput = true;
    g.type = "input";
    g.name = extract(s);
    g.no = Gate::cnt_gates;
    
    // Add gate number to input no vector
    inp_nos.push_back(Gate::cnt_gates);

    // Increment counters
    Gate::cnt_gates++;
    //Gate::cnt_inputs++;
    
    return g;
}

Gate createOutput(string s) {
    Gate g;
    g.isOutput = true;
    g.type = "output"; // It will be overwritten anyway
    g.name = extract(s);
    g.no = Gate::cnt_gates;
    //g.cnt_fout = 0;
    
    // Add gate number to output no vector
    outp_nos.push_back(Gate::cnt_gates);

    // Increment counters
    Gate::cnt_gates++;
    histo[1] += 1; // Primary output gates have 1 fanout
    //Gate::cnt_outputs++;
    
    return g;
}

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
        gateMap[splt[0]].type = returnStringBefore(splt[1], '(');
        /*if (!gateMap[splt[0]].isOutput) {
            gateMap[splt[0]].no = Gate::cnt_gates;
            Gate::cnt_gates++;
        }*/
        
        // Analyze input gates
        inGates = split(extract(splt[1]), ',');
        Gate ig;
        for (auto itr: inGates) {
            if (gateMap.insert({itr, ig}).second) {
                // New gate created, update name
                gateMap[itr].name = itr;
            }
            gateMap[itr].cnt_fout++;
            if (gateMap[itr].cnt_fout > max_fanout) {
                max_fanout = gateMap[itr].cnt_fout;
            }
            gateMap[splt[0]].gates_fin.push_back(itr);
        }
    }
}

void printResults(string s) {
    
    ofstream outfile;
    outfile.open(s+".out");
    //cout << "Map size: " << gateMap.size() << "\n" << endl;
    outfile << max_fanout << endl;
    for (int i = 0; i <= max_fanout; i++) {
        outfile << histo[i] << endl;
    }
    
    outfile << inp_nos.size();
    for (auto itr: inp_nos) {
        outfile << " " << itr;
    }
    
    outfile << "\n" << outp_nos.size();
    for (auto itr: outp_nos) {
        outfile << " " << itr;
    }
    
    outfile << endl;
    for (auto itr: type_stats) {
        outfile << itr.first << " " << itr.second.count << " " << 
                itr.second.fanout.size() << " " << 
                itr.second.fanin.size() << endl;
    }
    
    outfile.close();
    cout << "Results were printed: " << s << ".out" << endl;
}

/*
 * Main function
 */
int main(int argc, char** argv) {
    // Check arguments, input file should be provided
    if (argc < 2) {
        perror("Input file is not provided!");
        exit(0); // Exit the program
    } else {
        ifstream infile;
        infile.open(argv[1]);
        
        // Try to open the input file
        if (!infile.is_open()) { 
            perror("Error while opening the input file!");
        } else {        
            cout << "File opened: " << argv[1] << endl;
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
        
        // Iterate through the map to construct fanout histogram and
        // find fanin/fanout numbers of gate types.
        for (auto& itr: gateMap) {
            //cout << itr.first << " : " << itr.second.type << endl;
            // Histogram
            histo[itr.second.cnt_fout] += 1;
            /*if (itr.second.isOutput) {
                histo[1] += 1; // Output gates have 1 fanout
            }*/
            
            // Fanin/fanout analysis
            if (itr.second.type != "input") {
                // Try to create a tuple with Stats for that gate type
                // if there isn't any
                Stats s;
                if (!type_stats.insert({itr.second.type, s}).second) {
                    // If there is, increment count
                    type_stats[itr.second.type].count++;
                }
                
                // Analyze fanin gates
                if (!itr.second.gates_fin.empty()) {
                    //cout << "in if" << itr.second.name <<  endl;
                    for (auto& g_itr: itr.second.gates_fin) {
                        //cout << " in for" << endl;
                        //cout << g_itr << endl;
                        if (gateMap[g_itr].type == itr.second.type) {
                            //cout << " in 2. if" << endl;
                            type_stats[itr.second.type].fanout.insert(g_itr);
                            type_stats[itr.second.type].fanin.insert(itr.second.name);
                        }
                    }
                }
            }
        }
        
        printResults(returnStringBefore(argv[1], '.'));
    }
    
    return 0;
}
