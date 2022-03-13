# Varient-Type Option Map

## Save & Retrieve Varient-Type Values by std::map interface.
- **Saving values** <br>
An object can save value of int, double, char, vector<T>, map<key,T> or etc., just using '=' operator like python.
```cpp 
// example code  
COptMap A;
A["Put"] = 3.3;           // insert float value  
A["Here"] = "ABCDE";      // insert string value
A["Any"] = 3;             // insert int value 
std::vector<int> TmpVec = {1,2,3,4,5}   
A["Name"] = std::move(TmpVec);      //insert vector value
```
- **Constructing Hierarchy** <br>
The map-like COptMap class also have the value type of COptMap itself. This feature enables the COptMap can have hierarchical structure.
```cpp 
// example code   
COptMap NetOpt;                 // the top of hierarchy, here, all values of Neural Network.
COptMap tmpOptimOpt;            // Option map about optimizer
tmpOptimOpt["method"] = "adam";
tmpOptimOpt["learningrate"] = 0.001;
tmpOptimOpt["beta1"] = 0.9;
tmpOptimOpt["beta2"] = 0.999;
NetOpt["optimizer"] = std::move(tmpOptimOpt);   // tmpOptimOpt is moved to one of the map value of NetOpt;

std::vector<COptMap> tmpLayerOpt;     // Option map about layers
int NumLayer = 3;
tmpLayerOpt.resize(NumLayer); // Option Map about neuralnetwork optimizer
for (int i = 0; i < NumLayer; i++)
{
  COptMap & LyrOpt = tmpLayerOpt[i];
  LyrOpt["type"] = "fullyconndected";
  LyrOpt["dropout"] = 0.5;
  LyrOpt["initializer"] = "random";
}
NetOpt["layer"] = std::move(tmpLayerOpt); // tmpLayerOpt is moved to one of the map value of NetOpt
```
- **Retrieving values.** <br>
Type operator '=' to get the saved values when the left hand side has concrete type.  If lhs is generic type like 'auto' or template type, use getter function.
```cpp 
// A was generated above
double dVal = A["Put"];               // using operator
auto strVal = A.getString("Here");    // using getter function 
int nVal = A.getInt("Any");           // of course, using getter function and concrete lhs type
auto strVal = A.getVector("Name");
```
- **Retrieving values in hierarchical structure.** <br>
```cpp   
...
tmpOptimOpt = NetOpt["optimizer"];
std::string optimtype = tmpOptimOpt["method"];
double optimrate = tmpOptimOpt["learningrate"];
double beta1 = tmpOptimOpt["beta1"];
double beta2 = tmpOptimOpt["beta2"];

std::vector<COptMap> tmpLayerOpt = NetOpt["layer"]    // Option map about layers
...
```
## Features
- Save & retrive various typed data with one map object
- Provides python-like interface (an element has run-time type)
- Being saved & being retrived data should have the same type (o/w throw exception)
- STL Container Compatible
- Provides move sementic

## Install
- Download .h, .cpp files and include OptMap.h
- C++ Version : C++11 or above

## Implementation
The variant type class is made to include all option types, offenly used, such as fundamental types like char, unsigned char, int, ... and STL classes, namely std::string, std::map, std::vector. Saving STL class-type option values, we can more set option values diversely.
- Fundumental types and pointer to STL types are defined together as C++ UNION in the varient type element class.
- Classes heavely employ converting constructors and converting operator().

## Further works
- Writting enough test cases
- Performance improvement 
- Serialize, Import from & Export to a format (JSON, XML, etc...)
