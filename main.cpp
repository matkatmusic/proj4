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

#include <iostream>

int main()
{   
    //testing instruction 0
    HeapA heapA ; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << *( ft.add( 2.0f ).value ) << std::endl;
    std::cout << "FloatType subtract result=" << *( ft.subtract( 2.0f ).value ) << std::endl;
    std::cout << "FloatType multiply result=" << *( ft.multiply( 2.0f ).value ) << std::endl;
    std::cout << "FloatType divide result=" << *( ft.divide( 16.0f).value ) << std::endl << std::endl;

    std::cout << "DoubleType add result=" << *( dt.add(2.0).value ) << std::endl;
    std::cout << "DoubleType subtract result=" << *(dt.subtract(2.0).value) << std::endl;
    std::cout << "DoubleType multiply result=" << *(dt.multiply(2.0).value) << std::endl;
    std::cout << "DoubleType divide result=" << *(dt.divide(5.f).value) << std::endl << std::endl;

    std::cout << "IntType add result=" << *( it.add(2).value ) << std::endl;
    std::cout << "IntType subtract result=" << *( it.subtract(2).value ) << std::endl;
    std::cout << "IntType multiply result=" << *( it.multiply(2).value ) << std::endl;
    std::cout << "IntType divide result=" << *( it.divide(3).value ) << std::endl << std::endl;
    std::cout << "Chain calculation = " << *( (it.multiply(1000).divide(2).subtract(10).add(100)).value ) << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << *(ft.add( 3.0f ).multiply(1.5f).divide(5.0f).value) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << *(dt.value) << std::endl;
    std::cout << "Initial value of it: " << *(it.value) << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << *(dt.multiply(*it.value).divide(5.0f).add(*ft.value).value) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << *(it.divide(0).value) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << *(ft.divide(0).value) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << *(dt.divide(0).value) << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    std::cout << "good to go!\n";

    return 0;
}
