#include "PiecewiseLinear/PiecewiseLinearFunction.h"
PiecewiseLinearFunction::PiecewiseLinearFunction(std::vector<Point>&& points){
    std::sort(points.begin(), points.end(),
                    [](Point p0, Point p1){return p0.x < p1.x;}
    );
    for(size_t i = 1; i < points.size(); ++i){
        sectors_.emplace_back(Sector(points[i-1], points[i]));
    }
    currentSectorIt_= sectors_.begin();
}
std::vector<Point>
PiecewiseLinearFunction::toPointsVector(std::vector<double> const& x,
                                                    std::vector<double> const& y){
    std::vector<Point> res(x.size());
    size_t const minSize = std::min(x.size(), y.size());
    for(size_t i = 0; i < minSize; ++i){
        res[i] = Point{x[i], y[i]};
    }
    return res;
}

std::optional<Sector>
PiecewiseLinearFunction::getContainingSector(double x){
    if((*currentSectorIt_).contains(x)){
        return *currentSectorIt_;
    }else if(  (*(currentSectorIt_+1)).contains(x)){
        currentSectorIt_++;
        return *currentSectorIt_;
    }else if(  (*(currentSectorIt_-1)).contains(x)){
        currentSectorIt_--;
        return *currentSectorIt_;
    }
    return std::nullopt;
}
double
PiecewiseLinearFunction::operator()(double x){
        auto const& sector = getContainingSector(x);
        if(sector!=std::nullopt){
            return sector.value()(x);
        }
        throw std::runtime_error("Argument out of bounds");
    }
