# Introduction

This is an example implementation of dlopen API originally covered [here](https://tldp.org/HOWTO/html_single/C++-dlopen/).

## Precursor

Previously, we have used the [Polygon repo.](https://github.com/sakkammadam/polygon) to create library files (triangle.so) and (square.so)
We will copy the interface file (polygon.hpp) and the library files (triangle.so) and (square.so) to this repo.

## Implementation details

The goal here is to take a library file and integrate with one's calling programs. This is to facilitate runtime linkage.
This is accomplished by the dlopen API which is incorporated by dlfcn header file.

We will first load the triangle.so library file (line#8). It will proceed to exit the implementation if the file was unavailable.

We are loading "symbols" present in the library file which is *create* and *destroy* factory functions.

    // create a pointer to the factory function used to create Polygon (Triangle) and (Square)
    create_t* create_triangle = (create_t*)dlsym(triangle,"create");
    create_t* create_square = (create_t*)dlsym(square,"create");

    // create a pointer to the factory function used to delete Polygon (Triangle)
    destroy_t* destroy_triangle = (destroy_t*)dlsym(triangle,"destroy");

We will now use the newly declared function pointer (create_triangle) to create class instances

    // create an instance of the triangle class! Note that it points to base pointer!
    polygon* poly = create_triangle();
    polygon* poly = create_square();

We can use the destroy_triangle and destroy_square to delete the instance after use

    // destroy the instance
    destroy_triangle(poly);
    destroy_square(poly);

Lastly, we close the library handle

    // unload the handle
    dlclose(triangle);
    dlclose(square);

## Building

We will create an executable 

    g++ -o polyExec main.cpp polygon.hpp -ldl

To run the executable

    ./polyExec