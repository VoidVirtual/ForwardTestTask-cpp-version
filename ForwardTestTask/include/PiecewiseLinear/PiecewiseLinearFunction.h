#pragma once
#include <vector>
#include <exception>
#include <algorithm>
#include <optional>
#include <iostream>
#include "Sector.h"
class PiecewiseLinearFunction
{
public:
    virtual ~PiecewiseLinearFunction()=default;
    PiecewiseLinearFunction(std::vector<double>& args, std::vector<double>& values):
                                PiecewiseLinearFunction(std::move(toPointsVector(args,values)))
    {
    }
    PiecewiseLinearFunction(std::vector<Point>&& points);
    std::optional<Sector> getContainingSector(double x);
    double operator()(double x);
private:
    static std::vector<Point> toPointsVector(std::vector<double> const& x,
                                            std::vector<double> const& y);
private:
    std::vector<Sector>::const_iterator currentSectorIt_;
    std::vector<Sector> sectors_;
};
