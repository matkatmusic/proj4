#include <iostream>
#include <cmath>
#include <functional>
#include <memory>
#include <limits>

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

template<typename NumericType>
struct Numeric
{
    using T = Numeric;
    using Type = NumericType;

    Numeric(Type f) : value( new Type(f) ) { }
    
    template<typename OtherType>
    T& operator += (const OtherType& v) { *value += static_cast<Type>(v); return *this; }

    template<typename OtherType>
    T& operator -= (const OtherType& v) { *value -= static_cast<Type>(v); return *this; }

    template<typename OtherType>
    T& operator *= (const OtherType& v) { *value *= static_cast<Type>(v); return *this; }

    template<typename OtherType>
    T& operator /= (const OtherType& v) 
    { 
        if constexpr ( std::is_same<Type, int>::value )
        {
            if constexpr (std::is_same<OtherType, int>::value )
            {
                if( v == 0 )
                {
                    std::cout << "can't divide integers by zero!\n";
                    return *this;
                }
            }
            else if( std::abs(v) < std::numeric_limits<OtherType>::epsilon() )
            {
                std::cout << "can't divide integers by zero!\n";
                return *this;
            }
        }
        else if( std::abs(v) < std::numeric_limits<OtherType>::epsilon() )
        {
            std::cout << "warning: trying to divide by zero!\n";
        }

        *value /= static_cast<Type>(v);
        return *this; 
    }
    operator Type() const { return *value; }

    T& pow(Type f) { return powInternal(f); }

    using Func = void(*)(std::unique_ptr<Type>&);
    T& apply(Func f)
    {
        if( f )
            f(value);

        return *this;
    }

    T& apply(std::function<T&(std::unique_ptr<Type>&)> f)
    {
        if( f )
            return f(value);

        return *this;
    }
private:
    std::unique_ptr<Type> value;
    T& powInternal( float v )
    {
        *value = std::pow(*value, v);
        return *this;
    }
};

template<>
struct Numeric<double>
{
    using T = Numeric;
    using Type = double;

    Numeric(Type f) : value( new Type(f) ) { }
    
    T& operator += (Type v) { *value += v; return *this; }
    T& operator -= (Type v) { *value -= v; return *this; }
    T& operator *= (Type v) { *value *= v; return *this; }
    T& operator /= (Type v) { 
        if( v == 0.0 )
            std::cout << "warning: floating point division by zero!\n";

        *value /= v; 
        return *this; 
    }
    operator Type() const { return *value; }

    T& pow(Type f) { return powInternal(f); }

    template<typename Callable>
    T& apply(Callable f)
    {
        f(value);

        return *this;
    }
private:
    std::unique_ptr<Type> value;
    T& powInternal( float v )
    {
        *value = std::pow(*value, v);
        return *this;
    }
};

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
    Numeric<float> ft( 5.5f );
    Numeric<double> dt( 11.1 );
    Numeric<int> it ( 34 );
    Numeric<double> pi( 3.14 );

    // std::cout << "The result of FloatType^4 divided by IntType is: " << ft.multiply( ft ).multiply( ft ).divide( it ) << std::endl;
    ft *= ft;
    ft *= ft;
    ft /= static_cast<float>(it);
    std::cout << "The result of FloatType^4 divided by IntType is: " << ft << std::endl;

    // std::cout << "The result of DoubleType times 3 plus IntType is : " << dt.multiply( 3 ).add( it ) << std::endl;
    dt *= 3;
    dt += it;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt << std::endl;

    // std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it.divide( pi ).multiply( dt ).subtract( ft ) << std::endl;
    it /= static_cast<int>(pi);
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
    Numeric<float> ft1(2);
    Numeric<double> dt1(2);
    Numeric<int> it1(2);    
    int floatExp = 2.0f;
    int doubleExp = 2.0;
    int intExp = 2;
    Numeric<int> itExp(2);
    Numeric<float> ftExp(2.0f);
    Numeric<double> dtExp(2.0);
    
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
    Numeric<float> ft2(3.0f);
    Numeric<double> dt2(4.0);
    Numeric<int> it2(5);
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

template<typename T>
void myNumericFreeFunct(std::unique_ptr<T>& f) { *f += 7.0f; }

// void part6()
// {
//     FloatType ft3(3.0f);
//     DoubleType dt3(4.0);
//     IntType it3(5);
    
//     std::cout << "Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:" << std::endl;
//     std::cout << "ft3 before: " << ft3 << std::endl;
//     ft3.apply( [&ft3](float &value) -> FloatType&
//     {
//       value += 7.0f;
//       return ft3;
//     } );
//     std::cout << "ft3 after: " << ft3 << std::endl;
//     std::cout << "Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:" << std::endl;
//     std::cout << "ft3 before: " << ft3 << std::endl;
//     ft3.apply(myFloatFreeFunct);
//     std::cout << "ft3 after: " << ft3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;

//     std::cout << "Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:" << std::endl;
//     std::cout << "dt3 before: " << dt3 << std::endl;
//     dt3.apply( [&dt3](double &value) -> DoubleType&
//     {
//       value += 6.0;
//       return dt3;
//     } );
//     std::cout << "dt3 after: " << dt3 << std::endl;
//     std::cout << "Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:" << std::endl;
//     std::cout << "dt3 before: " << dt3 << std::endl;
//     dt3.apply(myDoubleFreeFunct);
//     std::cout << "dt3 after: " << dt3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;

//     std::cout << "Calling IntType::apply() using a lambda (adds 5) and IntType as return type:" << std::endl;
//     std::cout << "it3 before: " << it3 << std::endl;
//     it3.apply( [&it3](int &value) -> IntType&
//     {
//       value += 5;
//       return it3;
//     } );
//     std::cout << "it3 after: " << it3 << std::endl;
//     std::cout << "Calling IntType::apply() using a free function (adds 5) and void as return type:" << std::endl;
//     std::cout << "it3 before: " << it3 << std::endl;
//     it3.apply(myIntFreeFunct);
//     std::cout << "it3 after: " << it3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;    
// }

void part7()
{
    Numeric<float> ft3(3.0f);
    Numeric<double> dt3(4.0);
    Numeric<int> it3(5);
    
    std::cout << "Calling Numeric<float>::apply() using a lambda (adds 7.0f) and Numeric<float> as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;

    {
        using Type = decltype(ft3)::Type;
        ft3.apply( [&ft3](std::unique_ptr<Type> &value) -> decltype(ft3)&
        {
            *value += 7.0f;
            return ft3;
        } );
    }

    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "Calling Numeric<float>::apply() twice using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling Numeric<double>::apply() using a lambda (adds 6.0) and Numeric<double> as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;

    {
        using Type = decltype(dt3)::Type; 
        dt3.apply( [&dt3](std::unique_ptr<Type> &value) -> decltype(dt3)&
        {
            *value += 6.0;
            return dt3;
        } ); // This calls the templated apply fcn
    }
    
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "Calling Numeric<double>::apply() twice using a free function (adds 7.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply(myNumericFreeFunct<double>).apply(myNumericFreeFunct<double>); // This calls the templated apply fcn
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling Numeric<int>::apply() using a lambda (adds 5) and Numeric<int> as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;

    {
        using Type = decltype(it3)::Type;
        it3.apply( [&it3](std::unique_ptr<Type> &value) -> decltype(it3)&
        {
            *value += 5;
            return it3;
        } );
    }
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "Calling Numeric<int>::apply() twice using a free function (adds 7) and void as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "---------------------\n" << std::endl;    
}

int main()
{   
    //testing instruction 0
    HeapA heapA ; 

    //assign heap primitives
    Numeric<float> ft ( 2.0f );
    Numeric<double> dt ( 2 );
    Numeric<int> it ( 2 ) ;

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
    // part6();
    part7();
    std::cout << "good to go!\n";

    return 0;
}
