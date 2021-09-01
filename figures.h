#pragma once



// базовый класс фигуры (полиморфный)
struct Shape { virtual void f() {}; };

// прямоугольник
struct Rectangle : Shape { };

// треугольник
struct Triangle : Shape {};

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape * a, Shape * b) {return true;};

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape * a, Shape * b) {return true;};

