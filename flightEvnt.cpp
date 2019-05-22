#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
//-------------------------------------------------------------
// Binary Heap; Provided Function:
  class UnderflowException { };
  class IllegalArgumentException { };
  class ArrayIndexOutOfBoundsException { };
  class IteratorOutOfBoundsException { };
  class IteratorMismatchException { };
  class IteratorUninitializedException { };
  template <typename Comparable>
  class BinaryHeap{
    public:
      explicit BinaryHeap(int capacity = 100) : array(capacity+1), currentSize(0){ }
      explicit BinaryHeap(const vector<Comparable> &items) : array(items.size()+10), currentSize(items.size()){
        cout << "Construct w/ vector reached." << endl;
        for(int i=0; i<items.size(); i++)
          array[i+1] = items[i];
        buildHeap();
      }
      bool isEmpty() const{
        return currentSize == 0;
      }
      const Comparable &findMin() const{
        if(isEmpty())
          throw UnderflowException();
        return array[1];
      }
      void insert(const Comparable &x){
        if( currentSize == array.size()-1)
          array.resize(array.size()*2);
        int hole = ++currentSize;
        for(; hole> 1&&x<array[hole/2]; hole/=2)
          array[hole] = array[hole/2];
        array[hole] = x;
      }
      void deleteMin(){
        if(isEmpty())
          throw UnderflowException();
        array[1] = array[currentSize--];
        percolateDown(1);
      }
      void deleteMin(Comparable &minItem){
        if(isEmpty())
          throw UnderflowException();
        minItem = array[1];
        array[1] = array[currentSize--];
        percolateDown(1);
      }
      void makeEmpty(){
        currentSize = 0;
      }
    private:
      int currentSize;
      vector<Comparable> array;
      void buildHeap(){
        cout << "Build heap reached." << endl;
        for(int i=currentSize/2; i>0; i--)
          percolateDown(i);
      }
      void percolateDown(int hole){
        int child;
        Comparable tmp = array[hole];
        for(; hole*2 <= currentSize; hole=child){
          child = hole*2;
          if(child!=currentSize && array[child+1]<array[child])
            child++;
          if(array[child]<tmp)
            array[hole] = array[child];
          else
            break;
        }
        array[hole] = tmp;
      }
  };
//-------------------------------------------------------------
// Class of Flight Events, builds flight with info:
//Elements and functions are public just for ease of use,
//since they are used by the main function and binary heap class.
  class flightEvent{
    public:
      int eventTime, fltnum, gate; //key too event
      bool atGate=false;
      string from, goes; // Airport names, abbrev.
      flightEvent(){} //Default constructor
      void setEvent(int arr, string from, string goes){
        //Used to designate values to the object.
        this->eventTime = arr;
        this->from = from;
        this->goes = goes;
      }
      void printFlights(){
        cout << "Flight number " << fltnum << " from " << from
               << " set at " << eventTime << "." << endl;
      }
      bool operator>(flightEvent rhs) const{
        //Overloads "less than" to compare event times:
        if(eventTime > rhs.eventTime)
          return true;
        else
          return false;
      }
      bool operator<(flightEvent rhs) const{
        //Overloads "greater than" to compare event times:
        if(eventTime < rhs.eventTime)
          return true;
        else
          return false;
      }
  };
//-------------------------------------------------------------
// Functions for arrival and departure print outs:
  void arrivFlght(flightEvent curr){
    int minutes, hours;
    //Cvt event Time to hours and minutes for easy reading:
    hours = curr.eventTime/60;
    minutes = curr.eventTime - (hours*60);
    //Print info on arrival:
    cout << "🛬 ARR: Flight# " << curr.fltnum << " from " << curr.from << " to " << curr.goes << " : "
           << "Arriving  at " << hours << "h, " << minutes << "m. ";
    cout << "Assigned Gate: " << curr.gate << endl;
  }
  void departFlght(flightEvent curr){
    int minutes, hours;
    //Cvt event time to hours and minutes for easy reading:
    hours = curr.eventTime/60;
    minutes = curr.eventTime - (hours*60);
    //Print info on departure:
    cout << "🛫 DEP: Flight# " << curr.fltnum << " from " << curr.from << " to " << curr.goes << " : "
           << "Departing at " << hours << "h, " << minutes << "m. " ;
    cout << "Released Gate: " << curr.gate << endl;
  }
//-------------------------------------------------------------
// Main:
int main(){
  int n, currGate, fltNum=1000, delay;
  flightEvent currEvent;
//--------Gates Pushed To Stack---------
  cout << "Enter the number of gates for simulation: " << endl;
  cin >> n;
  stack<int> availGates; //Create stack for gats
  for (int i=0; i<n; i++) //Iterate and fill stack
    availGates.push(i+1); //Adds to stack gate number between 1 and n
//--------Build Schedule---------------
//Vector of flightEvent objects to set info for arrival flights:
  vector<flightEvent> arrival(14);
  arrival[0].setEvent(2, "LAX", "JFK");
  arrival[1].setEvent(3, "SMF","RDU");
  arrival[2].setEvent(4, "IAH","MSP");
  arrival[3].setEvent(9, "ABQ","ATL");
  arrival[4].setEvent(11, "SJC", "BOS");
  arrival[5].setEvent(14, "PHX", "MIA");
  arrival[6].setEvent(17, "SFO", "ORD");
  arrival[7].setEvent(19, "SLC", "AUS");
  arrival[8].setEvent(28, "TUL", "ONT");
  arrival[9].setEvent(33, "DCA", "LAS");
  arrival[10].setEvent(37, "BNA", "SEA");
  arrival[11].setEvent(44, "MAF", "AMA");
  arrival[12].setEvent(49, "HOS", "DEN");
  arrival[13].setEvent(55, "ELP", "MEM");
//------Fill Queue : Arrivals------
  BinaryHeap<flightEvent> planeHeap(336); //336 total in 24 hours
  for(int i=0; i<14; i++){ //For all 14 arrivals per hour
    for(int j=0; j<24; j++){ //For each flight per hour
      planeHeap.insert(arrival[i]); //Insert event to queue
      arrival[i].eventTime = arrival[i].eventTime + 60; //Add 60 minutes for next inner loop
    }
  }
//------Begin Simulation------
  cout << "=============================================================================" << endl;
  cout << "                          Begin Simulation:  " << endl;
  cout << "=============================================================================" << endl;
  while(!planeHeap.isEmpty()){ //Loop while events exist
      planeHeap.deleteMin(currEvent); //Pop next event into currEvent
      if (currEvent.atGate==false){ //If an arrival
        if (availGates.empty()){
          //If stack of gates is empty and arrival is next event, unsuccessful.
          cout << "              🚫 No more available gates. End Simulation. 🚫 " << endl;
          break;
        }
        currEvent.fltnum = fltNum; // Assign flight number
        fltNum++;
        currEvent.gate = availGates.top(); //Assign gate number
        availGates.pop();
        arrivFlght(currEvent); // Print info for this arrival.
        currEvent.atGate = true; // Set as atGate so next run is a departure
        //----------------------------------------
        //Determine if there is a delay with rand number generator:
        delay = rand() %100+1;
        if (delay>40) //60% chance of no delay
          currEvent.eventTime += 60;
        else {   //40% chance of delay
          delay = rand() %40+20; //Random number between 20 and 40
          currEvent.eventTime += (delay+60);
        }
        //-----------------------------------------
        planeHeap.insert(currEvent); //Set departure event
      }
      else if (currEvent.atGate==true){ // If a departure
        departFlght(currEvent); // Print out departure information
        currGate = currEvent.gate; // Get it's gate number
        availGates.push(currGate); // Put gate back on stack for use
        currEvent.atGate = false;
      }
  }
  cout << "=============================================================================" << endl;
  cout << "                          End of Simulation.  " << endl;
  cout << "=============================================================================" << endl;
  return 0;
}
