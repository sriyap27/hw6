#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {};
        int i = 4;
        int strInd = k.size() - 1;
        // adding the values to w
        while (strInd >= 0) {
            // getting the groups of 6 characters
            int substr[6] = {};
            if (strInd >= 5) {
                for (int m = 0; m < 6; m++) {
                    substr[m] = letterDigitToNumber(k[strInd - 5 + m]);
                }
                strInd -= 6; 
            }
            else {
                for (int m = 0; m <= strInd; m++) {
                    substr[5 - strInd + m] = letterDigitToNumber(k[m]);
                }
                strInd = -1;
            }
            // converting to decimal
            unsigned long long dec = substr[0];
            for (int n = 1; n < 6; n++) {
                dec = dec * 36 + substr[n];
            }
            w[i] = dec;
            i--;
        }
        HASH_INDEX_T hashVal = 0;
        for (int x = 0; x < 5; x++) {
            //std::cout << "w[" << x << "] = " << w[x] << std::endl;
            hashVal += (rValues[x] * w[x]);
        }
        return hashVal;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char lower = (char)tolower(letter);
        if (isdigit(lower)) {
            return (int) lower - '0' + 26;
        }
        else {
            return (int) lower - 'a';
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
