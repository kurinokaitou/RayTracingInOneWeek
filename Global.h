#pragma once
#include <iostream>
#include <cmath>
#include <random>

#undef M_PI
#define M_PI 3.141592653589793f
#undef EPSLION
#define EPSILON 1e-5

class Global
{
public:
    static bool solveQuadratic(const double& a, const double& b, const double& c, double& x0, double& x1)
    {
        double discr = b * b - 4 * a * c;
        if (discr < 0.0) return false;
        else if (discr == 0.0) x0 = x1 = -0.5 * b / a;
        else {
            float q = (b > 0.0) ?
                -0.5 * (b + sqrt(discr)) :
                -0.5 * (b - sqrt(discr));
            x0 = q / a;
            x1 = c / q;
        }
        if (x0 > x1) std::swap(x0, x1);
        return true;
    }
    static double deg2rad(const double& deg) { return deg * M_PI / 180.0; }
    static double clamp(const double& lo, const double& hi, const double& v)
    {
        return std::max(lo, std::min(hi, v));
    }
    static double getRamdomDouble(double min = -0.5, double max = -0.5)
    {
        static std::uniform_real_distribution<double> distribution(min, max);
        static std::mt19937 generator;
        return distribution(generator);
    }
};

