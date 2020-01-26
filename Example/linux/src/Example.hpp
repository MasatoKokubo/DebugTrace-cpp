/// ConsoleTest.hpp
/// (C) 2017 Masato Kokubo

#include <complex>
#include <iostream>
#include <limits>

/// Point
template <typename T> class Point {
    private:
        T _x = 0; // X value
        T _y = 0; // Y value

    public:
        // Default Constructor
        Point() = default;

        // Constructor
        Point(const T& v) noexcept : _x(v), _y(v) {
        }

        // Constructor
        Point(const T& x, const T& y) noexcept : _x(x), _y(y) {
        }

        // Copy Constructor
        Point(const Point<T>& p) noexcept : Point(p._x, p._y) {
        }

        // Destructor
        ~Point() = default;

        // Assignment Operator
        Point& operator =(const Point<T>& p) noexcept {
            _x = p._x;
            _x = p._x;
            return *this;
        }

        // Returns the X value.
        auto x() const noexcept {return _x;}

        // Returns the Y value.
        auto y() const noexcept {return _y;}

        // Transposes the X and Y value.
        auto transpose() const noexcept {return Point<T>(_y, _x);}

        // Returns a point created from the minimum value of each of the X and Y value.
        static constexpr auto min() {return Point<T>(std::numeric_limits<T>::min());}

        // Returns a point created from the maximum value of each of X and Y values.
        static constexpr auto max() {return Point<T>(std::numeric_limits<T>::max());}

        /// Reutrns the hash value.
        size_t hash() const {
            return (size_t)((size_t)_x * 31 + (size_t)_y);
        }
};

// Unary operators
template <typename T> auto operator +(const Point<T>& p) noexcept {return p;}
template <typename T> auto operator -(const Point<T>& p) noexcept {return Point<T>(-p.x(), -p.y());}

// Binary operators
template <typename T> auto operator +(const Point<T>& p, T v) noexcept {return Point<T>(p.x() + v, p.y() + v);}
template <typename T> auto operator -(const Point<T>& p, T v) noexcept {return Point<T>(p.x() - v, p.y() - v);}
template <typename T> auto operator *(const Point<T>& p, T v) noexcept {return Point<T>(p.x() * v, p.y() * v);}
template <typename T> auto operator /(const Point<T>& p, T v) noexcept {return Point<T>(p.x() / v, p.y() / v);}
template <typename T> auto operator %(const Point<T>& p, T v) noexcept {return Point<T>(p.x() % v, p.y() % v);}

template <typename T> auto operator +(const Point<T>& p1, const Point<T>& p2) noexcept {return Point<T>(p1.x() + p2.x(), p1.y() + p2.y());}
template <typename T> auto operator -(const Point<T>& p1, const Point<T>& p2) noexcept {return Point<T>(p1.x() - p2.x(), p1.y() - p2.y());}
template <typename T> auto operator *(const Point<T>& p1, const Point<T>& p2) noexcept {return Point<T>(p1.x() * p2.x(), p1.y() * p2.y());}
template <typename T> auto operator /(const Point<T>& p1, const Point<T>& p2) noexcept {return Point<T>(p1.x() / p2.x(), p1.y() / p2.y());}
template <typename T> auto operator %(const Point<T>& p1, const Point<T>& p2) noexcept {return Point<T>(p1.x() % p2.x(), p1.y() % p2.y());}

// Comparison operators
template <typename T> auto operator ==(const Point<T>& p1, const Point<T>& p2) noexcept {return p1.x() == p2.x() && p1.y() == p2.y();}
template <typename T> auto operator !=(const Point<T>& p1, const Point<T>& p2) noexcept {return p1.x() != p2.x() || p1.y() != p2.y();}
template <typename T> auto operator < (const Point<T>& p1, const Point<T>& p2) noexcept {return p1.y() <  p2.y() || p1.y() == p2.y() && p1.x() <  p2.x();}
template <typename T> auto operator <=(const Point<T>& p1, const Point<T>& p2) noexcept {return p1.y() <  p2.y() || p1.y() == p2.y() && p1.x() <= p2.x();}
template <typename T> auto operator > (const Point<T>& p1, const Point<T>& p2) noexcept {return p1.y() >  p2.y() || p1.y() == p2.y() && p1.x() >  p2.x();}
template <typename T> auto operator >=(const Point<T>& p1, const Point<T>& p2) noexcept {return p1.y() >  p2.y() || p1.y() == p2.y() && p1.x() >= p2.x();}

// Other calculations
template <typename T> auto abs(const Point<T>& p) noexcept {return Point<T>(abs(p.x()), abs(p.y()));}
template <typename T> auto min(const Point<T>& p1, const Point<T>& p2) noexcept {return Point<T>(p1.x() <= p2.x() ? p1.x() : p2.x(), p1.y() <= p2.y() ? p1.y() : p2.y());}
template <typename T> auto max(const Point<T>& p1, const Point<T>& p2) noexcept {return Point<T>(p1.x() >= p2.x() ? p1.x() : p2.x(), p1.y() >= p2.y() ? p1.y() : p2.y());}

// to_string
namespace std {
    template <typename T>
    string to_string(const Point<T>& p) {
        return '(' + to_string(p.x()) + ", " + to_string(p.y()) + ')';
    }

    template <typename T>
    string to_string(const complex<T>& comp) {
        return "(real:" + to_string(comp.real()) + ", imag:" + to_string(comp.imag()) + ')';
    }

}

namespace std {
    template <typename T> struct hash<Point<T>> {
    //    typedef Point<T> argument_type;
    //    typedef size_t result_type;

        size_t operator()(const Point<T>& key) const {
            return key.hash();
        }
    };
}

// ClassA
class ClassA {
    public:
        void func1() const noexcept;
        void func2() const noexcept;
        void func3() const noexcept;
        void func4() const noexcept;
};
