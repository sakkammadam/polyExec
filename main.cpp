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

    // load the square library
    void* square = dlopen("./square.so", RTLD_LAZY);

    // raise error if the library wasn't loaded
    if(!square){
        std::cerr << "Cannot load library: " << dlerror() << std::endl;
        return 1;
    }
    // reset errors
    dlerror();


    // load the symbols!
    // create a pointer to the factory function used to create Polygon (Triangle)
    create_t* create_triangle = (create_t*)dlsym(triangle,"create");

    // create a pointer to the factory function used to create Polygon (Square)
    create_s* create_square = (create_s*)dlsym(square,"create");

     const char* dlsym_error = dlerror();
    // check any error
     if(dlsym_error){
     std::cerr << "Cannot load symbol create: " << dlsym_error << std::endl;
        return 1;
    }

    // create a pointer to the factory function used to delete Polygon (Triangle)
    destroy_t* destroy_triangle = (destroy_t*)dlsym(triangle,"destroy");
    // create a pointer to the factory function used to delete Polygon (Square)
    destroy_s* destroy_square = (destroy_s*)dlsym(square,"destroy");
    dlsym_error = dlerror();
    // check any error
    if(dlsym_error){
        std::cerr << "Cannot load symbol destroy: " << dlsym_error << std::endl;
        return 1;
    }
    // create an instance of the triangle class! Note that it points to base pointer!
    polygon* poly_t = create_triangle();
    // create an instance of the square class! Note that it points to base pointer!
    polygon* poly_s = create_square();

    // use the poly instance
    poly_t->set_side_length(7);
    poly_s->set_side_length(8);
    // Return the area!
    std::cout << "The triangle's area is: " << poly_t->area() << std::endl;
    std::cout << "The square's area is: " << poly_s->area() << std::endl;

    // destroy the triangle instance
    destroy_triangle(poly_t);
    // destroy the square instance
    destroy_square(poly_s);

    // unload the handles
    dlclose(triangle);
    dlclose(square);

    return 0;
}
