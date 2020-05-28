#include <iostream>

struct A {};
struct HeapA
{
    HeapA() { a = new A(); }
    ~HeapA() { delete a; }
    A* a;
};


struct IntType;
struct DoubleType;

struct FloatType
{
    using T = FloatType;
    using F = FloatType;
    using I = IntType&;
    using D = DoubleType;

    FloatType(float f) : value( new float(f) ) { }
    ~FloatType() { delete value; }

    T& add(float v) { *value += v; return *this; }
    T& add( F& ft ) { return add(*ft.value); }
    T& add( I& it );
    T& add( D& dt );

    T& subtract(float v) { *value -= v; return *this; }
    T& subtract( F& ft ) { return subtract(*ft.value); }
    T& subtract( I& it );
    T& subtract( D& dt );

    T& multiply(float v) { *value *= v; return *this; }
    T& multiply( F& ft ) { return multiply(*ft.value); }
    T& multiply( I& it );
    T& multiply( D& dt );

    T& divide(float v) { 
        if( v == 0.f )
            std::cout << "warning: floating point division by zero!\n";

        *value /= v; 
        return *this; 
    }
    T& divide( F& ft ) { return multiply(*ft.value); }
    T& divide( I& it );
    T& divide( D& dt );

    float* value;
};

struct DoubleType
{
    using T = DoubleType;
    using F = FloatType;
    using I = IntType&;
    using D = DoubleType;

    DoubleType(double f) : value( new double(f) ) { }
    ~DoubleType() { delete value; }

    T& add(double v) { *value += v; return *this; }
    T& add( F& ft ) { return add(*ft.value); }
    T& add( I& it );
    T& add( D& dt ) { return add(*dt.value); }

    T& subtract(double v) { *value -= v; return *this; }
    T& subtract( F& ft ) { return subtract(*ft.value); }
    T& subtract( I& it );
    T& subtract( D& dt ) { return subtract(*dt.value); }

    T& multiply(double v) { *value *= v; return *this; }
    T& multiply( F& ft ) { return multiply(*ft.value); }
    T& multiply( I& it );
    T& multiply( D& dt ) { return multiply(*dt.value); }

    T& divide(double v) { 
        if( v == 0.0 )
            std::cout << "warning: floating point division by zero!\n";

        *value /= v; 
        return *this; 
    }
    T& divide( F& ft ) { return multiply(*ft.value); }
    T& divide( I& it );
    T& divide( D& dt ) { return multiply(*dt.value); }
    double* value;
};

struct IntType
{
    using T = IntType;
    using F = FloatType;
    using I = IntType&;
    using D = DoubleType;

    IntType(int f) : value( new int(f) ) { }
    ~IntType() { delete value; }

    T& add(int v) { *value += v; return *this; }
    T& add( F& ft ) { return add(*ft.value); }
    T& add( I& it ) { return subtract(*it.value); }
    T& add( D& dt ) { return add(*dt.value); }

    T& subtract(int v) { *value -= v; return *this; }
    T& subtract( F& ft ) { return subtract(*ft.value); }
    T& subtract( I& it ) { return subtract(*it.value); }
    T& subtract( D& dt ) { return subtract(*dt.value); }

    T& multiply(int v) { *value *= v; return *this; }
    T& multiply( F& ft ) { return multiply(*ft.value); }
    T& multiply( I& it ) { return multiply(*it.value); }
    T& multiply( D& dt ) { return multiply(*dt.value); }

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
    T& divide( F& ft ) { return multiply(*ft.value); }
    T& divide( I& it ) { return divide(*it.value); }
    T& divide( D& dt ) { return divide(*dt.value); }

    int* value;
};

FloatType& FloatType::add( I& it ) { return add(*it.value); }
FloatType& FloatType::add( D& dt ) { return add(*dt.value); }

FloatType& FloatType::subtract( I& it ) { return subtract(*it.value); }
FloatType& FloatType::subtract( D& dt ) { return subtract(*dt.value); }

FloatType& FloatType::multiply( I& it ) { return multiply(*it.value); }
FloatType& FloatType::multiply( D& dt ) { return multiply(*dt.value); }

FloatType& FloatType::divide( I& it ) { return divide(*it.value); }
FloatType& FloatType::divide( D& dt ) { return divide(*dt.value); }

DoubleType& DoubleType::add(IntType& it) { return add(*it.value); }
DoubleType& DoubleType::subtract(IntType& it) { return subtract(*it.value); }
DoubleType& DoubleType::multiply(IntType& it) { return multiply(*it.value); }
DoubleType& DoubleType::divide(IntType& it) { return divide(*it.value); }

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
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << *(dt.multiply(it).divide(5.0f).add(ft).value) << std::endl;

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
