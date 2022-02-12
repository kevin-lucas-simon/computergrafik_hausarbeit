#include "vector.h"
#include <assert.h>
#include <math.h>

// Konstruktor setzt die Variablen X,Y,Z
Vector::Vector( float x, float y, float z)
{
    X = x;
    Y = y;
    Z = z;
}

// Standardkonstruktor lässt die Member-Variablen X,Y,Z uninitialisiert
Vector::Vector() {}

// Berechnet das Skalarprodukt
float Vector::dot(const Vector& v) const
{
    return X*v.X + Y*v.Y + Z*v.Z;
}

// Berechnet das Kreuzprodukt
Vector Vector::cross(const Vector& v) const
{
    return Vector(Y*v.Z - Z*v.Y, Z*v.X - X*v.Z, X*v.Y - Y*v.X);
}



// Addition zweier Vektoren
Vector Vector::operator+(const Vector& v) const
{
    return Vector(X+v.X, Y+v.Y, Z+v.Z);
}

// Subtraktion zweier Vektoren
Vector Vector::operator-(const Vector& v) const
{
    return Vector(X-v.X, Y-v.Y, Z-v.Z);
}

// Skalierung eines Vektors
Vector Vector::operator*(float c) const
{
    return Vector(X*c, Y*c, Z*c);
}

// Negiert den Vektor
Vector Vector::operator-() const
{
    return Vector(-X, -Y, -Z);
}

// Addition zweier Vektoren
Vector& Vector::operator+=(const Vector& v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    return *this;
}




// Normalisiert den Vektor.
Vector& Vector::normalize()
{
    float length = this->length();
    if(length == 0)
        return *this;
    X = X/length;
    Y = Y/length;
    Z = Z/length;
    return *this;
}

// Gibt die Länge des Vektors zurück
float Vector::length() const
{
    return sqrt(lengthSquared());
}

// Gibt die quadratische Länge des Vektors zurück
float Vector::lengthSquared() const
{
    return pow(X,2) + pow(Y, 2) + pow(Z,2);
}

// Liefert den Reflexionsvektor zurück, normal ist die Normale der Oberfläche, die reflektiert
Vector Vector::reflection( const Vector& normal) const
{
    return *this-(normal*(this->dot(normal)))*2;
}

// Führt einen Kollisionstest zwischen einem Strahl und einem Dreieck durch
// d ist die Richtung des Strahls
// a,b,c sind die Vertizes des Dreiecks
// s gibt den Faktor des Auftreffpunkts zurück
bool Vector::triangleIntersection( const Vector& d, const Vector& a, const Vector& b, const Vector& c, float& s) const
{
    // Normale n und Abstand e von Koordinatenursprung zur Ebene definieren
    Vector n = (c-a).cross(b-a).normalize();
    float e = n.dot(a);

    // Prüfen, ob Vektor d parallel zum Dreieck verläuft
    if(d.dot(n) == 0)
        return false;

    // Schnittpunkt mit gesponnener Ebene bestimmen
    s = (e-n.dot(*this))/(n.dot(d));
    Vector p = *this+(d*s);

    // Prüfen, ob der Vektor in die richtige Richtung zeigt
    if(s < 0)
        return false;

    // Flächeninhalte berechnen
    float triangleArea = (c-a).cross(b-a).length()/2;
    float intersectionArea = (c-a).cross(p-a).length()/2 + (b-a).cross(p-a).length()/2 + (c-b).cross(p-b).length()/2;

    // Prüfen, ob der Schnittpunkt innerhalb des Dreiecks liegt (mit float Ungenauigkeit)
    float epsilon = pow(10, -6);
    return triangleArea >= intersectionArea - epsilon;
}
