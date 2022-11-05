#include "polygon.hpp"
#include <iostream>
#include <dlfcn.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    // load the triangle library
    void* triangle = dlopen("./triangle.so", RTLD_LAZY);
    // raise error if the library wasn't loaded
    if(!triangle){
        std::cerr << "Cannot load library: " << dlerror() << std::endl;
        return 1;
    }
    // reset errors
    dlerror();
    // load the symbols!
    // create a pointer to the factory function used to create Polygon (Triangle)
    create_t* create_triangle = (create_t*)dlsym(triangle,"create");
    const char* dlsym_error = dlerror();
    // check any error
    if(dlsym_error){
        std::cerr << "Cannot load symbol create: " << dlsym_error << std::endl;
        return 1;
    }
    // create a pointer to the factory function used to delete Polygon (Triangle)
    destroy_t* destroy_triangle = (destroy_t*)dlsym(triangle,"destroy");
    dlsym_error = dlerror();
    // check any error
    if(dlsym_error){
        std::cerr << "Cannot load symbol destroy: " << dlsym_error << std::endl;
        return 1;
    }
    // create an instance of the triangle class! Note that it points to base pointer!
    polygon* poly = create_triangle();

    // use the poly instance
    poly->set_side_length(7);
    // Return the area!
    std::cout << "The area is: " << poly->area() << std::endl;

    // destroy the instance
    destroy_triangle(poly);

    // unload the handle
    dlclose(triangle);

    return 0;
}
