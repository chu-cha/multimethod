#pragma once
#include <typeinfo>
#include <typeindex>
#include <utility>
#include <functional>
#include <map>


// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod
{
    typedef std::pair<std::type_index, std::type_index> argTypes;
    using fun = std::function<Result (Base*, Base*)>;
    std::map<argTypes, fun> implimentations;
    
    typename std::map<argTypes, fun>::const_iterator findElem(Base* a, Base* b)  const{
        auto getTypeInfo = [](Base* c) { return std::type_index(typeid(*c));} ;
        argTypes pair = make_pair(getTypeInfo(a), getTypeInfo(b));
        return implimentations.find(pair);
    };


    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid
    // f - это функция или функциональный объект
    // принимающий два указателя на Base
    // и возвращающий значение типа Result
    void addImpl( const std::type_info& t1,  const std::type_info& t2,  fun f )
    {
        implimentations.emplace(make_pair(std::type_index(t1), std::type_index(t2)), f);
    };

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно
        // проверить есть ли реализация для b и а

        return findElem(a, b) != implimentations.end() ||
               (Commutative && (findElem(b, a) != implimentations.end()));
    };

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        auto elem = findElem(a, b);
        if (elem != implimentations.end())
            return elem->second(a, b);

        return findElem(b, a)-> second(b, a);
    };
};