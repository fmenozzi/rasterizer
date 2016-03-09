#ifndef COLOR_H_
#define COLOR_H_

struct Color {
    float r, g, b;

    Color() : r(0), g(0), b(0) {}
    Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

    Color operator+(const Color& c) const { return Color(r+c.r, g+c.g, b+c.b); }
    Color operator*(float f)        const { return Color(r*f, g*f, b*f); }
    Color operator/(float f)        const { return Color(r/f, g/f, b/f); }

    Color& operator+=(const Color& c) { 
        r += c.r;
        g += c.g;
        b += c.b;

        return *this;
    }

    Color correct(float gamma) const;

    static Color white() {
        return Color(1,1,1);
    }

    static Color black() {
        return Color(0,0,0);
    }
};

#endif
