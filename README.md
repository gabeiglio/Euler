# Euler

Euler is a mathematical expression evaluator.
It features a recursive descent parser that directly compiles to bytecode (One pass)

### Use

Simple arithmetic
```
> (2 + 12) * (2 - -2) / 1
56
```
Trigonometric functions (sin, cos, tan)
```
> sin(12)
-0.53657291
```
Variable Assignment
```
> x = 1/2
x = 0.5
> x + 1
1.5
```
Function declaration
```
> f(x) = x * 2
f(x) = x * 2
> f(2)
4
```
### Features:
- Arithmetic expressions (addition, substraction, division and multiplication)
- Trigonometric functions sin, cos, tan
- Variable assignment (In progress)
- Function declarations (In progress)

### Installation
For now it has only been tested on OS X and clang so I would not be surprised if it only works on that enviroment.
Just clone the project and run ```make``` in the src directory.
