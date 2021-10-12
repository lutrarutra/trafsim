#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "time.h"

///////////////////////////////////////////////////////////////////////////////////////
//
//  class Rando generates random numbers
//  
//  function roll:
//      input:  meanvalue
//      output: random number (from normal distribution with meanvalue and with std 1.5 
//
//  function uniroll:
//      input:  endrange
//      output: random number between 1 and endrange 
// 
//  examples:
//      ts::Rando randomi(7);         
//      std::cout << randomi.roll() << '\n';        // output random around 7
//
//      ts::Rando sec_randomi(10);         
//      std::cout << sec_randomi.uniroll() << '\n'; // output random 1..10
//      
//////////////////////////////////////////////////////////////////////////////////

namespace ts
{
class Rando
{
private:
        std::random_device rd;
        int max_roll;
        typedef std::mt19937 MyRng;
        MyRng rng;
        std::normal_distribution<double> dice;
        std::uniform_int_distribution<int> unidice;  
public:
        // constructor initialize two random distributions
        // 1. normal distribution with mean value MR and std 1.5
        // 2. uniform distribution with range 1..MR 

        Rando(int MR, float std = 1.5f):max_roll(MR), rng(rd()), 
            dice(std::normal_distribution<>(MR,std)),
            unidice(std::uniform_int_distribution<>(1,MR))
        {
            // rng.seed(::time(NULL));
        }   
        ~Rando(){}

        // roll function returns normally distributed random values
        int roll(){ return dice(rng);}

        // uniroll function returns uniformly distributed random values
        int uniroll(){ return unidice(rng);}
        
    };
}
