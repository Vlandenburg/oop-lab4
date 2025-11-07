#pragma once
#include "figure.h"
#include "point.h"
#include <cmath>

#define TRIANGLE_POINTS 3

template <Number T>
class Triangle : public Figure<T> {
private:
    Point<T>* m_vertices;

public:
    Triangle() : m_vertices(nullptr) {}
    Triangle(Point<T> p1, Point<T> p2, Point<T> p3) {
        m_vertices = new Point<T>[TRIANGLE_POINTS];
        m_vertices[0] = p1; m_vertices[1] = p2; m_vertices[2] = p3;
    }
    ~Triangle() { delete[] m_vertices; }

    Triangle(const Triangle& other) {
        m_vertices = new Point<T>[TRIANGLE_POINTS];
        for(int i = 0; i < TRIANGLE_POINTS; ++i) m_vertices[i] = other.m_vertices[i];
    }
    Triangle& operator=(const Triangle& other) {
        if (this == &other) return *this;
        delete[] m_vertices;
        m_vertices = new Point<T>[TRIANGLE_POINTS];
        for(int i = 0; i < TRIANGLE_POINTS; ++i) m_vertices[i] = other.m_vertices[i];
        return *this;
    }

    void get_center(T* outX, T* outY) const override {
        if (!m_vertices) { *outX = 0; *outY = 0; return; }
        *outX = (m_vertices[0].X + m_vertices[1].X + m_vertices[2].X) / 3.0;
        *outY = (m_vertices[0].Y + m_vertices[1].Y + m_vertices[2].Y) / 3.0;
    }
    double get_area() const override {
        if (!m_vertices) return 0.0;
        double term1 = m_vertices[0].X * (m_vertices[1].Y - m_vertices[2].Y);
        double term2 = m_vertices[1].X * (m_vertices[2].Y - m_vertices[0].Y);
        double term3 = m_vertices[2].X * (m_vertices[0].Y - m_vertices[1].Y);
        return 0.5 * std::abs(term1 + term2 + term3);
    }
    void print(std::ostream& os) const override {
        if (!m_vertices) return;
        os << "Triangle: " << m_vertices[0] << " " << m_vertices[1] << " " << m_vertices[2];
    }
};