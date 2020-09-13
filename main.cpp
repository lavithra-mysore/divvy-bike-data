/*main.cpp*/

//
// Lavithra Mysore
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Project 6: DIVVY hashing program
// 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>    /*pair*/
#include <algorithm>  /*sort*/
#include <vector>

#include "hash.h"
#include "hashmap.h"
#include "util.h"
using namespace std;

//
//ordering
//
class ordering //it orders in such a way that gives priority second value in pair
{
public:
  bool operator()(const pair<double,double>& p1, const pair<double,double>& p2) const
  {
    //
    // if you want smaller values @ the end, return true if 
    // p1's value < p2's value.  if you want larger values
    // @ the end, return true if p1's value > p2's value.
    //
    if(p1.second==p2.second){
        return p1.first<p2.first;
    }
    return p1.second < p2.second;
  }
};

//
//ordering
//
class ordering2//it orders in such a way that gives priority first value of pair
{
public:
  bool operator()(const pair<double,double>& p1, const pair<double,double>& p2) const
  {
    return p1.first< p2.first;
  }
};

//
// StationData
// 

struct StationData// we use structure to use value in hashmap
{ // it stores value for station
	string Id;
	string Abbrev;
	string Name;
    string Lat;
    string Long;
    string Capacity;
    string OnlineDate;
    
	StationData()
	{
        
		Id="";
	    Abbrev="";
	    Name="";
        Lat="";
        Long="";
        Capacity="";
        OnlineDate="";
	}

};

//
// TripsData
// 
 
struct TripsData// we use structure to use value in hashmap of trips data
{ // it stores value for trips
	string TripId;
	string StartTime;
	string StopTime;
    string BikeId;
    string Duration;
    string From;
    string To;
    string Gender;
    string BirthYear;
	
	TripsData()
	{
        TripId="";
        StartTime="";
        StopTime="";
        BikeId="";
        Duration="";
        From="";
        To="";
        Gender="";
        BirthYear="";
	}
};

//
// string2int
// 
// Converts a string to an integer, unless string is empty, in
// which case 0 is returned.
// 
int string2int(string s)
{
	if (s == "")
		return 0;
	else
		return stoi(s);
}

//
// iinputDataStation
// 
// Given a filename denoting stations data,
// inputs that data into the given hash table.
// 
bool inputDataStation(string filename, hashmap<string, StationData*>& stationsById,hashmap<string, StationData*>& stationsByAbbrev)
{// it inputs data in stationsById and stationsByAbbrev 
	ifstream  infile(filename);
	
	if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	int count = 0;
	
	while (getline(infile, line))// if files opens 
	{
		stringstream s(line);
		
		string id, abbrev, name, lat,Long, capacity,onlineDate;
		
		//
		// format: date,xx xx xx xx xx,yy,z
		// 
		// NOTE: z may be missing (the multiplier)
		// 
		getline(s, id, ',');  // first value => id
		getline(s, abbrev, ',');   // second value => abbrev
		getline(s, name, ','); // third value => name
		getline(s, lat, ',');  // 4th value => lat
        getline(s, Long, ',');  // 5th value => Long
        getline(s, capacity, ','); // 6th value => capacity
        getline(s, onlineDate, ','); //7th value => onlineDate
		
		// we have input the 4 values, and since we are not
		// doing any arithmetic, we can just store them as
		// strings.  If the multiplier is missing then the
		// string is "", which is fine.
		
		//
		// store into hash table
		// 
		StationData* ld=new StationData();  // i allocate memory
		
		ld->Id = id; //assign values to all variables in struct 
		ld->Abbrev = abbrev;
		ld->Name = name;
        ld->Lat = lat;
		ld->Long = Long;
		ld->Capacity = capacity;
        ld->OnlineDate=onlineDate;

		stationsById.insert(id,ld, HashByStationID);// insert the struct in hashmap according to the id
        stationsByAbbrev.insert(abbrev,ld,HashByStationAbbrev);// insert the struct in hashmap according to the abbrev
		
		count++;
	}
	
	cout << "# of stations: " << count << endl;
	
	return true;  // we have data to be processed:
}

//
// inputDataTrips
// 
// Given a filename denoting trips data,
// inputs that data into the given hash table.
// 
bool inputDataTrips(string filename, hashmap<string,TripsData>& tripsById,hashmap<string, int>& bikesById)
{// it inputs data in tripsById and bikesbyId
	ifstream  infile(filename);
	
	if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	int count = 0;
    int bikes = 0;
	
	while (getline(infile, line))
	{
		stringstream s(line);
		
		string tripId, startTime,stopTime, bikeId,duration, from, to, gender, birthYear;
		
		
		 
		getline(s, tripId, ',');  
		getline(s, startTime, ',');   
		getline(s, stopTime, ',');
		getline(s, bikeId, ',');
        getline(s, duration, ',');
        getline(s, from, ',');
        getline(s, to, ',');
        getline(s, gender, ',');
        getline(s, birthYear, ',');
		
		// we have input the 9 values, and since we are not
		// doing any arithmetic, we can just store them as
		// strings.  If the multiplier is missing then the
		// string is "", which is fine.
		
		//
		// store into hash table
		// 
		TripsData ld;
        int usage=1;
		
		ld.TripId = tripId;
		ld.StartTime = startTime;
		ld.StopTime = stopTime;
        ld.BikeId = bikeId;
		ld.Duration = duration;
		ld.From = from;
        ld.To=to;
        ld.Gender = gender;
        ld.BirthYear=birthYear;
        
        bool found = bikesById.search(bikeId,usage,HashByBikeId);
        if(found==true){
            usage++;
            bikes--;
        }

		tripsById.insert(tripId,ld, HashByTripsId);// insert the struct in hashmap according to the tripId
        bikesById.insert(bikeId,usage,HashByBikeId);// insert the int in hashmap according to the BikeId
		
		count++;
        bikes++;
	}
	
	cout << "# of trips: " << count << endl;
    cout << "# of bikes: " << bikes << endl;
	
	return true;  // we have data to be processed:
}

//
// Help Function
// 
void help(){// if we user want to know what is input they can call input
    cout<<"Available commands\n";
    cout<<" Enter a station id (e.g. 341)\n";
    cout<<" Enter a station abbreviation (e.g. Adler)\n";
    cout<<" Enter a trip id (e.g. Tr10426561)\n";
    cout<<" Enter a bike id (e.g. B5218)\n";
    cout<<" Nearby stations (e.g. nearby 41.86 -87.62 0.5)\n";
    cout<<" Similar trips (e.g. similar Tr10426561 0.3)\n";
}

//
// station id function
// 
void stationId(string input,hashmap<string,StationData*>& stationsById){
    // it takes in id if it exist in file/struct it prints all data on it
    StationData* ld;

    bool found = stationsById.search(input, ld,HashByStationID);

    if (!found)
    {
      cout << "Station not found" << endl;
    }
    else
    {
      cout<<"Station:\n";
      cout << " Id: " << ld->Id<< endl;
      cout << " Abbrev: " << ld->Abbrev << endl;
      cout << " Fullname: " << ld->Name << endl;
      cout << " Location: (" << stod(ld->Lat)<<", "<< stod(ld->Long) <<")"<< endl;
      cout << " Capacity: " << ld->Capacity << endl;
      cout << " Online date: " << ld->OnlineDate<< endl;
    }
    
}

//
// station abbrev function
//
void stationAbbrev(string input,hashmap<string,StationData*>& stationsByAbbrev){
    // it takes in Abbrev of station if it exist in file/struct it prints all data on it
    StationData* ld;

    bool found = stationsByAbbrev.search(input, ld,HashByStationAbbrev);

    if (!found)
    {
      cout << "Station not found" << endl;
    }
    else
    {
      cout<<"Station:\n";
      cout << " Id: " << ld->Id<< endl;
      cout << " Abbrev: " << ld->Abbrev << endl;
      cout << " Fullname: " << ld->Name << endl;
      cout << " Location: (" << stod(ld->Lat)<<", "<< stod(ld->Long) <<")"<< endl;
      cout << " Capacity: " << ld->Capacity << endl;
      cout << " Online date: " << ld->OnlineDate<< endl;
    }
    
}

void TripsId(string input,hashmap<string,TripsData>& tripsById,hashmap<string,StationData*>& stationsById){
    // i take in trips id
    TripsData ld;
    StationData* ld1;
    bool found = tripsById.search(input, ld,HashByTripsId);
    
    if (!found)
    {
      cout << "Trip not found" << endl;
    }
    else
    { // display trip id data
      cout<<"Trip:\n";
      cout << " Id: " << ld.TripId<< endl;
      cout << " StartTime: " << ld.StartTime << endl;
      cout << " Bikeid: " << ld.BikeId<< endl;
        
      cout << " Duration: " ;
        
      int time=stoi(ld.Duration);
        
      if(time>3600){ // convert time from sec form to hour minutes and sec
         cout<<time/3600<<" hours, ";
         time=time%3600;
      }
      cout<<time/60<<" minutes, "<<time%60<<" seconds"<<endl;
        
      bool found1=stationsById.search(ld.From, ld1,HashByStationID);
      if(found1==true){ // we use from id in tripsData to find abbrev of from station
          cout << " From station: " <<ld1->Abbrev<<" ("<<ld.From<<")"<< endl;
      }
        
      found1=stationsById.search(ld.To, ld1,HashByStationID);
      if(found1==true){// we use to id in tripsData to find abbrev of to station
          cout << " To station: " <<ld1->Abbrev<<" ("<<ld.To<<")"<< endl;
      }
        
      cout << " Rider identifies as: " << ld.Gender << endl;
      cout << " BirthYear: " << ld.BirthYear<< endl;
    }
    
}

void BikesId(string input,hashmap<string, int>& bikesById){
    // use bike id to print out all data
    int usage=0;
    bool found = bikesById.search(input,usage,HashByBikeId);
    
    if (!found)
    { 
      cout << "Bike not found" << endl;
    }
    else{
        cout<<"Bike:\n";
        cout << " Id: " <<input<< endl;
        cout << " Usage: " <<usage<< endl;
        
    }
}

vector<pair<int,double>> nearByStation(hashmap<string,StationData*>& stationsById,int N,double Long,double Lat, double miles){
 //i create function to return a vector with all the stations in miles radius from the coordinates 
    vector<pair<int,double>>  NearbyStations;
    
    for(int i=0;i<N;i++){ // i loop around arry in harshmap using valueAccess
         StationData* ld;
         bool find = stationsById.valueAccess(i,ld);
        
        if(find==true){ // if it is not empty calculate distance and check the radius
            double distance=distBetween2Points(Lat, Long, stod(ld->Lat),stod(ld->Long));
            
            if(distance<=miles){ //inser if its in that miles in the vector
                NearbyStations.push_back(make_pair(stod(ld->Id),distance));
            }            
        }        
    }
    return NearbyStations;   
}

void printNearByStation(string input,hashmap<string,StationData*>& stationsById,int N){
    
    vector<pair<int,double>> NearbyStations; 
    
    string Long;
    string Lat;
    string miles;
        
    input=input.erase(0,7); // i allter the input to the variables i need
    
    size_t found = input.find(" ");
    
    if(found!=string::npos){
       Lat=input.substr(0,found);
       input=input.erase(0,found+1);
    }
    
    found = input.find(" "); 
    if(found!=string::npos){
        Long=input.substr(0,found);
        miles=input.erase(0,found+1);
    }
    // i call function nearByStation to get all the station in that area
    NearbyStations= nearByStation(stationsById,N,stod(Long),stod(Lat),stod(miles));
    // i sort it and print it out
    sort(NearbyStations.begin(),NearbyStations.end(), ordering());
    
    cout<<"Stations within "<<miles<<" miles of ("<<Lat<<", "<<Long<<")\n";
    
    if(NearbyStations.empty()==true){
        cout<<" none found\n";
    }     
      for (auto p : NearbyStations){
            cout<<" station "<<p.first<<": "<<p.second<<" miles"<<endl;
     }
}

void similarTrips(string input,hashmap<string,StationData*>& stationsById,hashmap<string,TripsData>& tripsById,int N){
    
    string miles;
    
    double fromLong=0;
    double fromLat=0;
    
    double toLong=0;
    double toLat=0;
    double trips=0;
    
    TripsData ld;
    StationData* ld1;
    string tripInput;
    
    vector<pair<int,double>> SRadius; 
    vector<pair<int,double>> DRadius;

    // i alter that data to variables i can use 
    input=input.erase(0,8);

    size_t found = input.find(" ");
 
    if(found != string::npos){
        tripInput=input.substr(0,found);
        miles=input.erase(0,found+1);
    }
    cout<<"Trips that follow a similar path (+/-"<<miles<<" miles) as "<<tripInput<<endl;
    
    bool find = tripsById.search(tripInput, ld,HashByTripsId);
    // if trip exist take further variable like cordinates 
    if (!find)//else return " no such trip"
    {
      cout << " no such trip" << endl;
    }
    else{   
         stationsById.search(ld.From, ld1,HashByStationID);
         fromLong=stod(ld1->Long);
         fromLat= stod(ld1->Lat);
        
         stationsById.search(ld.To, ld1,HashByStationID);
        
         toLong=stod(ld1->Long);
         toLat= stod(ld1->Lat);
    }
    // input all stations in s cord and d cord in SRadius and DRadius
    SRadius= nearByStation(stationsById,10000,fromLong,fromLat,stod(miles));
    DRadius= nearByStation(stationsById,10000,toLong,toLat,stod(miles));
    // i sorts SRadius and DRadius
    sort(SRadius.begin(),SRadius.end(), ordering2());
    sort(DRadius.begin(),DRadius.end(), ordering2());
    
    for(int i=0;i<N;i++){ // i loop around array
        
        TripsData value;
        StationData* ld2;
        
        if(tripsById.valueAccess(i,value)==true){
             stationsById.search(value.From, ld2,HashByStationID);
            
             double tripFromLong=stod(ld2->Long);
             double tripFromLat= stod(ld2->Lat);

             stationsById.search(value.To, ld2,HashByStationID);

             double tripToLong=stod(ld2->Long);
             double tripToLat= stod(ld2->Lat);

             double fromDistance =distBetween2Points(tripFromLat,tripFromLong,fromLat, fromLong);
             double toDistance =distBetween2Points(tripToLat,tripToLong,toLat, toLong);
  
            if((fromDistance<=stod(miles))&&(toDistance<=stod(miles))){// if distance between 
                    trips++;// cords is under miles  of both from distance and to distance
            }       // i increment trip 
            
        }
        
    }// i print out SRadius ,DRadius and trips 
    if(find){
        cout<<" nearby starting points: ";

        for (auto p : SRadius ){
                cout<<p.first<<" ";
        }
        cout<<endl;

        cout<<" nearby ending points: ";

        for (auto p : DRadius ){
                cout<<p.first<<" ";
        }

        cout<<endl;

        cout<<" trip count: "<<trips<<endl; 
    }
}

void deleteStationData(int N,hashmap<string,StationData*>& stationsById,hashmap<string,StationData*>& stationsByAbbrev){
    // i free the memory at the end
    for(int i=0;i<N;i++){
        StationData* ld;
        bool find = stationsByAbbrev.valueAccess(i,ld);
        
        if(find==true){
            ld=nullptr;
        }
        
    }    
    
    for(int i=0;i<N;i++){
         StationData* ld;
         bool find = stationsById.valueAccess(i,ld);
        
         if(find==true){
                 delete(ld);
            }
        }        
}


int main()
{
	cout << "** DIVVY analysis program **" << endl;
	cout << endl;

	//
	// Allocate our hash table: 12 * 31 * 100 = 37,200
	// possible permutations:
	// 
    const int N = 10000;
    const int N1 = 2500000;
    const int N2 = 50000;
    
	hashmap<string,StationData*> stationsById(N);
    hashmap<string,StationData*> stationsByAbbrev(N);
    hashmap<string,TripsData> tripsById(N1);
    hashmap<string, int> bikesById(N2);

	//
	// Input data in hashmaps
	// 
	string filename;
    string filename1;
    
    cout<<"Enter stations file> ";// i take in different files
    getline(cin,filename); 
    
    cout<<"Enter trips file> ";
    getline(cin,filename1);
        
	cout << "\nReading "<<filename <<endl;
    cout << "Reading "<<filename1 <<endl<<endl;
    
	bool success = inputDataStation(filename, stationsById,stationsByAbbrev);
	
	//
	// did we input anything?
	// 
	if (!success) // if trip doesn't open it exists
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}

	
	success = inputDataTrips(filename1,tripsById,bikesById);
	
	//
	// did we input anything?
	// 
	if (!success)
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}
	
	//
	// allow the user to lookup DIVVY data:
	// 
 	string input;
	
	cout << endl;
	cout << "Please enter a command, help, or #> ";
	getline(cin,input);

 	//
 	// user testing:
	//
 	while (input != "#")
 	{ // different inputs are called for various inputs
     if(input=="#"){
            break;
        }
     if(input=="help"){
         help();
     }
     else if(isNumeric(input)==true){
         stationId(input,stationsById);
     }
        
     else if(input.substr(0,2)=="Tr"){
         TripsId(input,tripsById,stationsById);
         
     }
     else if(input.substr(0,1)=="B"){
         BikesId(input,bikesById);
         
     }
     else if(input.substr(0,6)=="nearby"){
         printNearByStation(input,stationsById,N);
         
     }
     else if(input.substr(0,7)=="similar"){// similar Tr10426561 0.5
        similarTrips(input,stationsById,tripsById,N1);
         
     }
         
     else{
         stationAbbrev(input,stationsByAbbrev);
     }

 	  cout << endl;
	  cout << "Please enter a command, help, or #> ";
	  getline(cin,input);
 	}
	
	//
	// done!
	// 
	cout << endl;
    deleteStationData(N,stationsById,stationsByAbbrev);// i free up the memory
	return 0;
}
