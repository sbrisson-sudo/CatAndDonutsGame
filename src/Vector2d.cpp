#include "Vector2d.h"

#include <cmath>

// vector - vector operators
Vector2D Vector2D::operator+(Vector2D const& xb){
    Vector2D res(this->x + xb.x, this->y + xb.y);
    return res;
}
Vector2D Vector2D::operator-(Vector2D const& xb){
    Vector2D res(this->x - xb.x, this->y - xb.y);
    return res;
}
Vector2D& Vector2D::operator+=(Vector2D const& xb){
    this->x += xb.x;
    this->y += xb.y;
    return *this;
}
Vector2D& Vector2D::operator-=(Vector2D const& xb){
    this->x -= xb.x;
    this->y -= xb.y;
    return *this;
}


// vector - scalar operators

Vector2D Vector2D::operator+(int n){
    Vector2D res(this->x + n, this->y + n);
    return res;
}
Vector2D Vector2D::operator-(int n){
    Vector2D res(this->x - n, this->y - n);
    return res;
}
Vector2D Vector2D::operator+(double z){
    Vector2D res(this->x + z, this->y + z);
    return res;
}
Vector2D Vector2D::operator-(double z){
    Vector2D res(this->x - z, this->y - z);
    return res;
}
Vector2D Vector2D::operator*(int n){
    Vector2D res(this->x * n, this->y * n);
    return res;
}
Vector2D Vector2D::operator*(double z){
    Vector2D res(this->x * z, this->y * z);
    return res;
}
Vector2D Vector2D::operator/(int n){
    Vector2D res(this->x * n, this->y * n);
    return res;
}
Vector2D Vector2D::operator/(double z){
    Vector2D res(this->x / z, this->y / z);
    return res;
}

// stream operators

ostream& operator<<(ostream& out, const Vector2D& v){
    out << "(" << v.x << "," << v.y << ")";
    return out;
}

// norms

double Vector2D::l2Norm(){
    return sqrt(x*x+y*y);
}

Vector2D Vector2D::unitVector(){
    double l2norm = this->l2Norm();
    Vector2D res(this->x / l2norm, this->y / l2norm);
    return res;
}