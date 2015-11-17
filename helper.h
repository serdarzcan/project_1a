/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   helper.h
 * Author: szc
 *
 * Created on November 15, 2015, 5:54 PM
 */

#ifndef HELPER_H
#define HELPER_H

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

//using namespace std;

// Preconstruct the results to split a string
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// Return a new vector which has results of splitting
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

// Function to remove spaces in a string
std::string removeSpaces(std::string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    return s;
}

// Extract string in between parentheses
std::string extract(std::string s) {
    unsigned first = s.find('(');
    unsigned last = s.find(')');
    return s.substr(first+1, last-first-1);
}


#endif /* HELPER_H */

