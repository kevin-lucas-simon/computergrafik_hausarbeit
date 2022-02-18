#include "color.h"
#include <assert.h>

// Aufruf des Standardkonstruktors setzt die Farbe auf schwarz
Color::Color()
{
    R = 0.0f;
    G = 0.0f;
    B = 0.0f;
}

// Aufruf des Konstruktors setzt die Farbe anhand der übergebenen Parametern
Color::Color( float r, float g, float b)
{
    R = r;
    G = g;
    B = b;
}

// Multipliziert den Farbwert mit einer anderen Farbe
Color Color::operator*(const Color& c) const
{
    return Color(R*c.R, G*c.G, B*c.B);
}

// Multipliziert den Farbwert mit fixem Wert
Color Color::operator*(const float Factor) const
{
    return Color(R*Factor, G*Factor, B*Factor);
}

// Addiert den Farbwert mit einer anderen Farbe
Color Color::operator+(const Color& c) const
{
    return Color(R+c.R, G+c.G, B+c.B);
}

// Addiert den Farbwert mit einer anderen Farbe
Color& Color::operator+=(const Color& c)
{
    R += c.R;
    G += c.G;
    B += c.B;
    return *this;
}

// Übergibt die Farbe als monochromen Wert
float Color::monochrome() const {
    return (R+G+B)/3;
}