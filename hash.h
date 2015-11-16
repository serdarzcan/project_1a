/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hash.h
 * Author: szc
 *
 * Created on November 15, 2015, 9:20 PM
 */

#ifndef HASH_H
#define HASH_H

class Hash
{
    public:
        size_t operator()(const std::string &s) const {
            return std::hash<std::string>()(s);
        }
};

#endif /* HASH_H */

