# Option Manager

## Variant Type Class
Sometimes it is needed one class saves different types of data by conditions. For example, an object saves int-type data when I put int-type in it, or double when I put double, just like python ! Especially, it is useful to save option values where performance is not that important. <br>
C++ *auto* or *template* cannot be used as the variant type class should understand conditions at *RUNTIME*. Rather, there are some solution for this : std::variant (C++20), OLE-based variant class. However, I develop my program in ~ C++14 environment, so cannot use std::variant, and I want the variant class contain STL containers like std::map or std::vector in addition to c++ funumantal types. <br>
The variant type class here is made for containing all offenly used option types such as fundamental types like char, unsigned char, int, ... and STL classes like std::string, std::map, std::vector. Saving STL class-type option values, we can more set option values diversely.

## Features
- Save & retrive variant type data
- Provides python-like interface when saving & retriving data
- Being saved & being retrived data should have the same type (o/w throw exception)
- Can put as STL Containers' Template Parameter
- Provides move constructors and assignment

## Install
- Requires C++11
- Download .h, .cpp files and include all headers

## Implementation
- Fundumental types are implemented with C++ UNION
- STL types as member variables. 

## How to Use
1. Option save
2. Option retrieve

## Limit
- No enough test cases
