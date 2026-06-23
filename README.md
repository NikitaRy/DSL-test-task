# DSL-test-task

This is a simple C code generator for PI-regulator with arithmetic & logical blocks.

## Input format

We have .xml file with blocks-dag. *We suppose that graph has no cycles.*

## What we do and why

### Install tinyxml2

We use this lib because it is lightweight. Maybe, if we have to implement more complex DSL, we choose more powerful lib like libxml (native, use C API).

Install with vcpkg:

 ```sh
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
    ./vcpkg integrate install
    ./vcpkg install tinyxml2
```
