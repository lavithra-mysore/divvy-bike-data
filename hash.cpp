/*hash.cpp*/

// Lavithra Mysore
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Hashing of dates and lottery numbers
// 

#include <iostream>
#include <string>
#include <cctype>  /*isdigit*/
#include <regex>   /*regular expressions*/

#include "hash.h"

using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
bool isNumeric(string s)
{
	//
	// A string is numeric if it contains 1 or more digits, so let's
	// use a regular expression to check that.
	//
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [[:d:]] means match a single digit.
	// The + means match the preceding sub-expression 1 or more times.
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}


//
// HashByStationID
// 
//
int HashByStationID(string Id, int N)
{

	return stoi(Id) % N;
}
//
// HashByStationID
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int HashByStationID(string Id)
{
  return HashByStationID(Id, 10000);
}

//
// HashByStationAbbrev
// e.g. 2112 W Peterson, 63rd Beach and Albany & Montrose
// Daniel J. Bernstein created a popular multiplicative string hash function 
// that uses an initial value of 5381 and a multiplier of 33
// 
int HashByStationAbbrev(string Abbrev, int N)
{
    size_t found = Abbrev.find(" ");
    
    while(found != string::npos){// remove all the space
       
        Abbrev.erase(found,1);
       found = Abbrev.find(" "); 
    }
    
    found = Abbrev.find("&");// remove & as it is commonly used
    
    if(found != string::npos){
       Abbrev.erase(found,1); 
    }

    unsigned long stringHash = 5381;
    
    for (auto c : Abbrev) { // Uses Daniel J. Bernstein's hash function
        stringHash = (stringHash << 5) + stringHash + char(c);
    }

	return stringHash % N;
}
//
// HashByStationAbbrev
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int HashByStationAbbrev(string Abbrev)
{
  return HashByStationAbbrev(Abbrev, 10000);
}

//
// HashByTripsId
// e.g. Tr10406143,Tr10425649,Trxxxxxxxx
// 
int HashByTripsId(string tripId, int N)
{
   string Id = tripId.substr(2); 
   
    return stoi(Id) % N; 
}
//
// HashByTripsId
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int HashByTripsId(string Abbrev)
{
  return HashByTripsId(Abbrev, 2500000);
}

//
// HashByBikeID
// e.g. B5218,B4199,Bxxxx
// 
int HashByBikeId(string bikeId, int N)
{
   string Id = bikeId.substr(1);  //xxxx
   return stoi(Id) % N;
}
//
// HashByBikeId
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int HashByBikeId(string bikeId)
{
  return HashByBikeId(bikeId, 50000);
}