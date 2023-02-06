# VLQ C++ Library

## Description
A variable-length quantity (VLQ) is a universal code that uses an arbitrary number of binary octets (eight-bit bytes) to represent an arbitrarily large integer. A VLQ is essentially a base-128  representation of an unsigned integer with the addition of the eighth bit to mark continuation of bytes. VLQ is identical to LEB128 except in endianness.   

VLQ C++ Lib contains static lib build and shared lib build for vlq encoding and decoding.  
Target of this lib is easy for C++ projects to analysis `js map file` or other VLQ encode and decode project.  

## Build
### static lib
`cmake -B build`  
lib location:  
`./build/libvlq.a` (unix system)  
### shared lib
`cmake -B build`  
`cd build`  
`sudo ninja install`  
`sudo cp /usr/local/lib/libvlq-shared.so /lib`  

## Run tests
### install gtest
`sudo apt-get install libgtest-dev && cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make && cd ./lib && sudo cp *.a /usr/lib && sudo ln -s /usr/lib/libgtest.a /usr/local/lib/libgtest.a && sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/libgtest_main.a`  
### run tests
`cd build && ninja vlq_test`  

## API
### encode
```C++
  vlq::Processor processor;
  std::vector<int> values{0, 0, 0, 0};
  std::string result = processor.encode(values); // AAAA
```
### decode 
```C++
  vlq::Processor processor;
  auto result = processor.decode("AAAA"); // {0, 0, 0, 0}
```

## VLQ Doc
[WIKI](https://en.wikipedia.org/wiki/Variable-length_quantity)  

