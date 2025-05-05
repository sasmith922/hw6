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
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        int len = k.length();
        int group = 0;

        // process starting from end of string in chunks of 6
        for (int i = len; i > 0 && group < 5; i -= 6, ++group) 
        {
            unsigned long long chunkVal = 0;
            //unsigned long long power = 1;

            // pocess each character in chunk
            for (int j = std::max(0, i - 6); j < i; ++j) 
            {
                char c = std::tolower(k[j]); // make char lowercase
                int val;
                if (c >= 'a' && c <= 'z') val = c - 'a';
                else if (c >= '0' && c <= '9') val = 26 + (c - '0');
                else val = 0;

                chunkVal = chunkVal * 36 + val;
            }

            w[4 - group] = chunkVal;
        }

        // Compute final hash with dot product of rValues and w
        unsigned long long hash = 0;
        for (int i = 0; i < 5; ++i) 
        {
            hash += rValues[i] * w[i];
        }

        return static_cast<HASH_INDEX_T>(hash);

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = std::tolower(letter);
        if (letter >= 'a' && letter <= 'z') // getting value if its a letter
        {
            return letter - 'a';
        }
        
        if (letter >= '0' && letter <= '9') // getting value if its a number
        {
            return 26 + (letter - '0');
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
