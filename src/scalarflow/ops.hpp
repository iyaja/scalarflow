#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <functional>

typedef std::function<float(float,float)> Function;
typedef std::string ID;

typedef float f32;
typedef std::vector<float> vf32;
typedef int i32;

#define REGISTER(id, expr) { id, [] (f32 a, f32 b) { return expr; } },
#define INPUT(id) { id, [] (f32 a, f32 b) { f32 x; std::cin >> x; return x; } },
// #define  OUTPUT(id) { id, [] (f32 a, f32 b) { std::cout << a << std::endl; return a; } },
#define OUTPUT(id) { id, [] (f32 a, f32 b) { return a; } },
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


// typedef std::function<float(vector<float>)> Function;

// #define REGISTER(id, expr) { id, [] (vf32 x) { return expr; } },
// #define INPUT(id) { id, [] (vf32 x) { f32 i; std::cin >> i; return i; } },
// #define OUTPUT(id) { id, [] (vf32 x) { std::cout << x[0] << std::endl; return x[0]; } },
// #define CONSTANT(id) { id, [] (vf32 x) { return x[0]; } },

// std::map<ID, Function> ops = {

//     INPUT("input")
//     OUTPUT("output")
//     CONSTANT("const")

//     REGISTER("add", x[0] + x[1])
//     REGISTER("mul", x[0] * x[1])
//     REGISTER("sub", x[0] - x[1])
//     REGISTER("div", x[0] / x[1])

// };