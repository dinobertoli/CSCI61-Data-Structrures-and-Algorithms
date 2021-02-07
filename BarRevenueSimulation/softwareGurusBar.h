#ifndef SOFTWAREGURUSBAR_H
#define SOFTWAREGURUSBAR_H

#include <iostream>
#include "simulationFramework.h"
#include <fstream>

/*
 *Discrete Event-Driven Simulation
 *Project 2
 *Dino Bertoli
 *6/1/19
 *
 *softwareGurusBar contains classes and fuctions for generating random ints and the bar itslef,
 * responsible for ordering-adding to profit, seating-determines if space is available and subtracts from available chairs,
 * and leaving-adds to available seating
 *
*/

SimulationFramework theSimulation;

//returns a random positive integer with max as parameter
class randomInteger {
  public:
  unsigned int operator ( ) (unsigned int);
} randomizer;

unsigned int randomInteger::operator ( ) (unsigned int max)
{
  unsigned int rval = rand( );
  return rval % max;
}

//returns a random positive int within range of low and high
unsigned int randBetween(int low, int high) {
  //return rand()%(high-low + 1) + low;
  return low + randomizer(high - low);
}



class SoftwareGurusBar {
  public:
    ofstream file;
    // try with 50 chairs, then try with 40, 60, ...
    // in order to find out “optimal” profit prospects
    SoftwareGurusBar( ): file ("output.txt"){
      unsigned int seats;
      cout << "Enter the number of seats" << endl;
      cin >> seats;
      freeChairs = seats;
      profit = 0.0;
     }
    bool canSeat (unsigned int numberOfPeople); // slide 15
    void order(unsigned int beerType); // slide 16
    void leave(unsigned int numberOfPeople); // slide 16
    unsigned int freeChairs;
    double profit;
};

SoftwareGurusBar theBar;

//determines if space is available and subtracts from available chairs
bool SoftwareGurusBar::canSeat (unsigned int numberOfPeople)
{
  // if sufficient room, then seat customers
  file << "Time: " << theSimulation.currentTime;
  file << " Group of " << numberOfPeople << " customers arrives";
  if (numberOfPeople < freeChairs) {
    file << " Group is seated" << endl;
    freeChairs -= numberOfPeople;
    return true;
  }
  else {
    file << " No room, group leaves" << endl;
    return false;
  }
}


//responsible for ordering-adding to profit
void SoftwareGurusBar::order (unsigned int beerType)
{
  string beer;
  if(beerType == 0){
    beer = "local beer";
  }
  else if(beerType == 1){
    beer = "special beer";
  }
  else{beer = "imported beer"; }
  // serve beer
  file << "Time: " << theSimulation.currentTime;
  file << " serviced order for " << beer << endl;
  if(beerType == 0){
    profit += 5.00;
  }
  else if(beerType == 1){
    profit += 6.00;
  }
  else{
    profit += 7.00;
  }
}

//adds to available seating
void SoftwareGurusBar::leave (unsigned int numberOfPeople)
{
  // people leave, free up chairs
  file << "Time: " << theSimulation.currentTime;
  file << " group of size " << numberOfPeople << " leaves" << endl;
  freeChairs += numberOfPeople;
}


#endif
