![Build Status](https://github.com/RicoP/ros/workflows/cppci/badge.svg)
# ros
A collection of single header files

`include/refptr.h`
* A simple reference counted mart pointer. Less powerful than shared_ptr but also less clutered. Allows circular safe pointers with refptr<T>::view
  
`include/range.h`
* A simple utility function to iterate over ranges without repeating the same `for(int i =...` pattern. 


Checkout the `test` folder for corresponding code samples. 
