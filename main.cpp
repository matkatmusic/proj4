#include <iostream>
#include <cmath>

struct A {};
struct HeapA
{
    HeapA() { a = new A(); }
    ~HeapA() { delete a; }
    A* a;
};

struct FloatType;
struct IntType;
struct DoubleType;

struct FloatType
{
    using T = FloatType;

    FloatType(float f) : value( new float(f) ) { }
    ~FloatType() { delete value; }

    T& operator += (float v) { *value += v; return *this; }
    T& operator -= (float v) { *value -= v; return *this; }
    T& operator *= (float v) { *value *= v; return *this; }
    T& operator /= (float v) { 
        if( v == 0.f )
            std::cout << "warning: floating point division by zero!\n";

        *value /= v; 
        return *this; 
    }
    operator float() const { return *value; }

    T& pow(float f) { return powInternal(f); }
    T& pow(const IntType& it);
    T& pow(const DoubleType& dt);
    T& pow(const FloatType& ft);
private:
    float* value;
    T& powInternal( float v )
    {
        *value = std::pow(*value, v);
        return *this;
    }
};

struct DoubleType
{
    using T = DoubleType;

    DoubleType(double f) : value( new double(f) ) { }
    ~DoubleType() { delete value; }

    T& operator += (double v) { *value += v; return *this; }
    T& operator -= (double v) { *value -= v; return *this; }
    T& operator *= (double v) { *value *= v; return *this; }
    T& operator /= (double v) { 
        if( v == 0.0 )
            std::cout << "warning: floating point division by zero!\n";

        *value /= v; 
        return *this; 
    }
    operator double() const { return *value; }
    T& pow(double f) { return powInternal(f); }
    T& pow(const IntType& it);
    T& pow(const DoubleType& dt);
    T& pow(const FloatType& ft);
private:
    double* value;
    T& powInternal( double v )
    {
        *value = std::pow(*value, v);
        return *this;
    }
};

struct IntType
{
    using T = IntType;

    IntType(int f) : value( new int(f) ) { }
    ~IntType() { delete value; }

    T& operator += (int v) { *value += v; return *this; }
    T& operator -= (int v) { *value -= v; return *this; }
    T& operator *= (int v) { *value *= v; return *this; }
    T& operator /= (int v) { 
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
    operator int() const { return *value; }
    T& pow(int f) { return powInternal(f); }
    T& pow(const IntType& it);
    T& pow(const DoubleType& dt);
    T& pow(const FloatType& ft);
private:
    int* value;
    T& powInternal( int v )
    {
        *value = static_cast<int>(std::pow(*value, v));
        return *this;
    }
};

FloatType& FloatType::pow(const FloatType& ft) { return pow( static_cast<float>(ft) ); }
FloatType& FloatType::pow(const DoubleType& dt) { return pow( static_cast<float>(dt) ); }
FloatType& FloatType::pow(const IntType& it) { return pow( static_cast<float>(it) ); }

DoubleType& DoubleType::pow(const FloatType& ft) { return pow( static_cast<double>(ft) ); }
DoubleType& DoubleType::pow(const DoubleType& dt) { return pow( static_cast<double>(dt) ); }
DoubleType& DoubleType::pow(const IntType& it) { return pow( static_cast<double>(it) ); }

IntType& IntType::pow(const FloatType& ft) { return pow( static_cast<int>(ft) ); }
IntType& IntType::pow(const DoubleType& dt) { return pow( static_cast<int>(dt) ); }
IntType& IntType::pow(const IntType& it) { return pow( static_cast<int>(it) ); }

#include <iostream>

struct Point
{
    Point(float a, float b) : x(a), y(b) { } 
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    void toString()
    {
        std::cout << "Point { x: " << x << ", y: " << y << " }" << "\n";
    }
private:
    float x{0}, y{0};
};

void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    // std::cout << "The result of FloatType^4 divided by IntType is: " << ft.multiply( ft ).multiply( ft ).divide( it ) << std::endl;
    ft *= ft;
    ft *= ft;
    ft /= it;
    std::cout << "The result of FloatType^4 divided by IntType is: " << ft << std::endl;

    // std::cout << "The result of DoubleType times 3 plus IntType is : " << dt.multiply( 3 ).add( it ) << std::endl;
    dt *= 3;
    dt += it;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt << std::endl;

    // std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it.divide( pi ).multiply( dt ).subtract( ft ) << std::endl;
    it /= pi;
    it *= dt;
    it -= ft;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it << std::endl;
    
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    // std::cout << it.multiply(it).divide(0).divide(0.0f).divide(0.0)<<std::endl;
    it *= it;
    it /= 0;
    it /= 0.0f;
    it /= 0.0;
    std::cout << it << std::endl;
    
    // std::cout << "FloatType x IntType  =  " << it.multiply( ft ) << std::endl;
    it *= ft;
    std::cout << "FloatType x IntType  =  " << it << std::endl;

    // std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it.add( dt ).add( ft ).multiply( 24 ) << std::endl;
    it += dt;
    it += ft;
    it *= 24;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it << std::endl;
}

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    FloatType ft1(2);
    DoubleType dt1(2);
    IntType it1(2);    
    int floatExp = 2.0f;
    int doubleExp = 2.0;
    int intExp = 2;
    IntType itExp(2);
    FloatType ftExp(2.0f);
    DoubleType dtExp(2.0);
    
    // Power tests with FloatType
    std::cout << "Power tests with FloatType " << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;  

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType " << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(ftExp)  << std::endl;    
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;    

    // Power tests with IntType
    std::cout << "Power tests with IntType " << std::endl;
    std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
    std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
    std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(ftExp)  << std::endl;    
    std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(dtExp)  << std::endl;    
    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    FloatType ft2(3.0f);
    DoubleType dt2(4.0);
    IntType it2(5);
    float floatMul = 6.0f;

    // Point tests with float
    std::cout << "Point tests with float argument:" << std::endl;
    Point p0(ft2, floatMul);
    p0.toString();   
    std::cout << "Multiplication factor: " << floatMul << std::endl;
    p0.multiply(floatMul); 
    p0.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with FloatType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p1(ft2, ft2);
    p1.toString();   
    std::cout << "Multiplication factor: " << ft2 << std::endl;
    p1.multiply(ft2); 
    p1.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with DoubleType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p2(ft2, static_cast<float>(dt2));
    p2.toString();   
    std::cout << "Multiplication factor: " << dt2 << std::endl;
    p2.multiply(dt2); 
    p2.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(ft2, static_cast<float>(dt2));
    p3.toString();   
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2); 
    p3.toString();   
    std::cout << "---------------------\n" << std::endl;
}

int main()
{   
    //testing instruction 0
    HeapA heapA ; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << ft.operator+=( 2.0f ) << std::endl;
    std::cout << "FloatType subtract result=" << ft.operator-=( 2.0f ) << std::endl;
    std::cout << "FloatType multiply result=" << ft.operator*=( 2.0f ) << std::endl;
    std::cout << "FloatType divide result=" << ft.operator/=( 16.0f) << std::endl << std::endl;

    std::cout << "DoubleType add result=" << dt.operator+=(2.0) << std::endl;
    std::cout << "DoubleType subtract result=" << dt.operator-=(2.0) << std::endl;
    std::cout << "DoubleType multiply result=" << dt.operator*=(2.0) << std::endl;
    std::cout << "DoubleType divide result=" << dt.operator/=(5.f) << std::endl << std::endl;

    std::cout << "IntType add result=" << it.operator+=(2) << std::endl;
    std::cout << "IntType subtract result=" << it.operator-=(2) << std::endl;
    std::cout << "IntType multiply result=" << it.operator*=(2) << std::endl;
    std::cout << "IntType divide result=" << it.operator/=(3) << std::endl << std::endl;
    std::cout << "Chain calculation = " << (it.operator*=(1000).operator/=(2).operator-=(10).operator+=(100)) << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft.operator+=( 3.0f ).operator*=(1.5f).operator/=(5.0f) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt << std::endl;
    std::cout << "Initial value of it: " << it << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << dt.operator*=(it).operator/=(5.0f).operator+=(ft) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << it.operator/=(0) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << ft.operator/=(0) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << dt.operator/=(0) << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    part3();
    part4();
    std::cout << "good to go!\n";

    return 0;
}
