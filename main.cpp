#include <iostream>

struct A {};
struct HeapA
{
    HeapA() { a = new A(); }
    ~HeapA() { delete a; }
    A* a;
};

struct FloatType
{
    using T = FloatType;

    FloatType(float f) : value( new float(f) ) { }
    ~FloatType() { delete value; }

    T& add(float v) { *value += v; return *this; }
    T& subtract(float v) { *value -= v; return *this; }
    T& multiply(float v) { *value *= v; return *this; }
    T& divide(float v) { 
        if( v == 0.f )
            std::cout << "warning: floating point division by zero!\n";

        *value /= v; 
        return *this; 
    }

    float* value;
};

struct DoubleType
{
    using T = DoubleType;

    DoubleType(double f) : value( new double(f) ) { }
    ~DoubleType() { delete value; }

    T& add(double v) { *value += v; return *this; }
    T& subtract(double v) { *value -= v; return *this; }
    T& multiply(double v) { *value *= v; return *this; }
    T& divide(double v) { 
        if( v == 0.0 )
            std::cout << "warning: floating point division by zero!\n";

        *value /= v; 
        return *this; 
    }

    double* value;
};

struct IntType
{
    using T = IntType;

    IntType(int f) : value( new int(f) ) { }
    ~IntType() { delete value; }

    T& add(int v) { *value += v; return *this; }
    T& subtract(int v) { *value -= v; return *this; }
    T& multiply(int v) { *value *= v; return *this; }
    T& divide(int v) { 
        if( v == 0 )
        {
            std::cout << "error: integer division by zero is an error and will crash the program!\n";
        }
        else
        {
            *value /= v; 
        }
        
        return *this; 
    }
    int* value;
};

int main()
{   
    
}
