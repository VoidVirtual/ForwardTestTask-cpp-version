struct Point{
    double x;
    double y;
};
class LinearFunction{
public:
    LinearFunction(Point const& p0, Point const& p1){
        if(p0.x==p1.x){
            throw std::runtime_error("Not a linear function");
        }
        k_ = (p1.y - p0.y) / (p1.x - p0.x);
        b_ = (p1.x * p0.y - p1.y * p0.x) / (p1.x - p0.x);
    }
    double operator()(double x)const{
        return k_*x + b_;
    }
    double k_;
    double b_;
};
struct Sector{
    Point left_;
    Point right_;
    Sector(Point const& left, Point const& right):
                            left_(left),
                            right_(right),
                            linearFunction_(left, right)
    {
    }
    double operator()(double x)const{
        return linearFunction_(x);
    }
    bool contains(double x)const{
        return (left_.x <= x) && (x <=right_.x);
    }
    LinearFunction linearFunction_;
};
