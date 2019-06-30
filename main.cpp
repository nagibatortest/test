#include <iostream>


/*      Typelist        */
class NullType {};

template <class T=NullType, class U=NullType>
struct Typelist
{
    typedef T head;
    typedef U Tail;
};


/*      Length      */
template <class TList>
struct Length;

template <>
struct Length<NullType>
{
    enum { value = 0 };
};

template <class T, class U>
struct Length< Typelist<T, U> >
{
    enum { value = 1 + Length<U>::value };
};

template <>
struct Length<Typelist<> >
{
    enum { value = 0 };
};

/*      TypeAt      */
template <class TList, unsigned int index>
struct TypeAt;

template <class Head, class Tail>
struct TypeAt<Typelist<Head, Tail>, 0>
{
    typedef Head Result;
};

template <class Head, class Tail, unsigned int index>
struct TypeAt<Typelist<Head, Tail>, index>
{
    typedef typename TypeAt<Tail, index - 1>::Result Result;
};


/*      Append       */
template <class TList, class T>
struct Append;

template <>
struct Append<NullType, NullType>
{
    typedef NullType Result;
};

template <class T>
struct Append<NullType, T>
{
    typedef Typelist<T, NullType> Result;
};

template <class Head, class Tail>
struct Append<NullType, Typelist<Head, Tail> >
{
    typedef Typelist<Head, Tail> Result;
};

template <class Head, class Tail, class T>
struct Append<Typelist<Head, Tail>, T>
{
    typedef Typelist<Head, typename Append<Tail, T>::Result> Result;
};


/*      Remove      */
template <class TList, class T>
struct Remove;

template <class T>
struct Remove<NullType, T>
{
    typedef NullType Result;
};

template <class T, class Tail>
struct Remove<Typelist<T, Tail>, T>
{
    typedef Tail Result;
};

template <class Head, class Tail, class T >
struct Remove<Typelist<Head, Tail>, T>
{
    typedef Typelist<Head, typename Remove<Tail, T>::Result> Result;
};


/*      Print       */
template <typename TypeList>
void Print() {
    std::cout << typeid(typename TypeList::head).name() << " ";
    Print<typename TypeList::Tail>();
};

template <>
void Print<NullType>() {
    return;
}


/*      Удаление первых N элементов Typelist        */
template<class TList, int N>
struct RemoveN{
    typedef NullType Result;
};

template <>
struct RemoveN<Typelist<>, 0>
{
    typedef Typelist<> Result;
};

template <class Head, class Tail>
struct RemoveN<Typelist<Head, Tail>, 0>
{
    typedef Typelist<Head, Tail> Result;
};

template<class Head, class Tail, int N>
struct RemoveN<Typelist<Head, Tail>, N>
{
    typedef typename RemoveN<Typelist<Tail>, N - 1>::Result Result;
};


/*      Линейная иерархия       */
template<class TList, template <class AtomicType, class Base> class Unit, class Root, int Length>
struct GenLinearHierarchy;

template<class Head, class Tail, template <class, class> class Unit, class Root>
struct GenLinearHierarchy<Typelist<Head, Tail>, Unit, Root, 1> : public Unit<Head, Root > {};

template<class Head, class Tail, template <class, class> class Unit, class Root, int Length>
struct GenLinearHierarchy<Typelist<Head, Tail>, Unit, Root, Length>
        : public Unit<Head, GenLinearHierarchy<Typelist<Tail>, Unit, Root, Length - 1> > {};

template<class T, template <class, class> class Unit, class Root, int Length>
struct GenLinearHierarchy<Typelist<T>, Unit, Root, Length> : public Unit<T, Root> {};


/*      N-ое число Фибоначчи     */
template <int N>
struct FibonacciNumber {
    enum { value = FibonacciNumber<N - 1>::value + FibonacciNumber<N - 2>::value };
};

template <>
struct FibonacciNumber<1> {
    enum { value = 1 };
};

template <>
struct FibonacciNumber<2> {
    enum { value = 1 };
};


/*      Иерархия Фибоначчи      */
template<class TList, template <class AtomicType, class Base> class Unit, class Root = NullType, int index = 1, int FibNumber = 1>
struct GenFibonacciHierarchy;

template<template <class, class> class Unit, class Root, int index, int FibNumber>
struct GenFibonacciHierarchy<Typelist<>, Unit, Root, index, FibNumber> {};

template<class T, template <class, class> class Unit, class Root, int index, int FibNumber>
struct GenFibonacciHierarchy<Typelist<T>, Unit, Root, index, FibNumber> : public Unit<T, Root> {
    typedef Unit<T, Root> LeftBase;
};

template<class Head, class Tail, template <class, class> class Unit, class Root, int index, int FibNumber>
struct GenFibonacciHierarchy<Typelist<Head, Tail>, Unit, Root, index, FibNumber> :
        public GenLinearHierarchy<Typelist<Head, Tail>, Unit, Root, FibNumber>,
        public GenFibonacciHierarchy<typename RemoveN<Typelist<Head, Tail>, FibNumber>::Result, Unit, Root, index + 1, FibonacciNumber<index>::value> {
    typedef Typelist<Head, Tail> TList;
    typedef GenLinearHierarchy<Typelist<Head, Tail>, Unit, Root, FibNumber> LeftBase;
    typedef GenFibonacciHierarchy<typename RemoveN<Typelist<Head, Tail>, FibNumber>::Result, Unit, Root, index + 1, FibonacciNumber<index>::value> RightBase;
};

/*      Тестрование     */
typedef Typelist<char, Typelist<short, Typelist<int, Typelist<long, Typelist<char, Typelist<short , Typelist<int, Typelist<long, NullType> > > > > > > > TL;

template <class T, class Base>
struct EventHandler : public Base
{
public:
    virtual void OnEvent(T& obj) {};
};

typedef GenFibonacciHierarchy<TL, EventHandler> FH;

int main() {
    std::cout << "Typelist: ";
    Print<TL>();
    std::cout << std::endl;

    std::cout << "Length Typelist: " << Length<TL>::value << std::endl;

    std::cout << "Typelist[0]: " << typeid(TypeAt<TL, 0>::Result).name() << std::endl;

    std::cout << "Append int: ";
    Print<Append<TL, int>::Result>();
    std::cout << std::endl;

    std::cout << "Remove char: ";
    Print<Remove<TL, char>::Result>();
    std::cout << std::endl;

    std::cout << "Fibonacci 10: " << FibonacciNumber<10>::value << std::endl;

    return 0;
}