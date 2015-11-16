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

//using namespace std;

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

