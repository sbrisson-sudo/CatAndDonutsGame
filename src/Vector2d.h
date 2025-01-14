#ifndef VECTOR2D
#define VECTOR2D

#include <iostream>
using namespace std;

class Vector2D {
public :
    double x,y;

    Vector2D() : x(0.0), y(0.0) {};
    Vector2D(double x, double y) : x(x), y(y) {};
    Vector2D(int x, int y) : x((double)x), y((double)y) {};

    Vector2D operator+(Vector2D const& xb);
    Vector2D operator-(Vector2D const& xb);
    Vector2D& operator+=(Vector2D const& xb);
    Vector2D& operator-=(Vector2D const& xb);
    Vector2D operator+(int n);
    Vector2D operator-(int n);
    Vector2D operator+(double z);
    Vector2D operator-(double z);
    Vector2D operator*(int n);
    Vector2D operator*(double z);
    Vector2D operator/(int n);
    Vector2D operator/(double z);

    friend ostream& operator<<(ostream& os, const Vector2D &v);

    double l2Norm();
    Vector2D unitVector();
};


#endif // VECTOR2D