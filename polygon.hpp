#ifndef POLYGON_POLYGON_HPP
#define POLYGON_POLYGON_HPP

class polygon{
protected:
    double side_length;
public:
    // Constructor
    polygon():side_length(0){};

    // Destructor
    virtual ~polygon(){};

    // Setter
    void set_side_length(double side_length_){
        this->side_length = side_length_;
    }

    // Area Calculation
    virtual double area() const = 0;

};

// Class factories - note the function signatures!
typedef polygon* create_t();
typedef void destroy_t(polygon*);

#endif //POLYGON_POLYGON_HPP
