#include <bits/floatn-common.h>
#include <iostream>
#include <map>
#include <string>
#include <functional>

typedef std::function<float(float,float)> Function;
typedef std::string ID;

typedef float f32;
typedef int i32;

#define REGISTER(id, expr) { id, [] (f32 a, f32 b) { return expr; } },
#define INPUT(id) { id, [] (f32 a, f32 b) { f32 x; std::cin >> x; return x; } },
#define OUTPUT(id) { id, [] (f32 a, f32 b) { std::cout << a << std::endl; return a; } },
#define CONSTANT(id) { id, [] (f32 a, f32 b) { return a; } },

std::map<ID, Function> ops = {

    INPUT("input")
    OUTPUT("output")
    CONSTANT("const")

    REGISTER("add", a + b)
    REGISTER("mul", a * b)
    REGISTER("sub", a - b)
    REGISTER("div", a / b)

};