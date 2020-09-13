/*hash.h*/

//
// Lavithra Mysore
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Hashing of dates and lottery numbers 
// 

#include <string>

using namespace std;

bool isNumeric(string s);
int HashByStationID(string Id, int N);
int HashByStationAbbrev(string Abbrev, int N);
int HashByTripsId(string tripId, int N);
int HashByBikeId(string bikeId, int N);
