# Option Manager

## Variant Type Class
- **A class that can contain variant types of data by conditions.** <br>
An object saves int-type data when one put int-type in it, or double when put double, just like python. <br> <br>
- **Saving and retrieving option values of various types.** <br>
For implementing these operation in the C++ programming language, it is needed to check the type of the variable in runtime, then allocate to/retrieve from the memory which is formated by the type of th variable. So it is slightly slower to use this variant type class than to use ordinary types, and it is recommended to used for saving option values where operation speed is not a main concern. <br><br>

## Features
- Save & retrive various typed data with one class type
- Provides python-like interface where the type of the object is determined implicitly
- Being saved & being retrived data should have the same type (o/w throw exception)
- Can be put as STL Containers' Template Parameter
- Provides move constructors and assignment

## Install
- Requires C++11
- Download .h, .cpp files and include all headers

## Implementation
C++ *auto* or *template* cannot be used used for contain variant type as the type should be inferred at *RUNTIME*. Rather, there are some solution for this : std::variant (C++20), traditional variant classes (such as OLE). However, it was needed to  develop my program in ~ C++14 environment, so cannot use std::variant, and I want the variant class contain STL containers like std::map or std::vector in addition to c++ funumantal types. <br>
The variant type class here is made for containing all offenly used option types such as fundamental types like char, unsigned char, int, ... and STL classes like std::string, std::map, std::vector. Saving STL class-type option values, we can more set option values diversely.
- Fundumental types are implemented with C++ UNION
- STL types as member variables. 
- Heavely employed converting constructors and converting operator().


## How to Use
1. Option save
2. Option retrieve

## Limit
- No enough test cases
