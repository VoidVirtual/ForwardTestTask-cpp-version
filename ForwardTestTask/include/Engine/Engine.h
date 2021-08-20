#pragma once
#include "EngineTester/EngineTester.h"
#include "EngineTester/EngineTestResult.h"
#include <functional>
#include <fstream>
class Engine{
    public:
        virtual ~Engine()=default;
        Engine(){
            enginesNum_++;
            id_ = enginesNum_;
        }
        size_t getId()const{return id_;}
        virtual std::shared_ptr<EngineTestResult> accept(EngineTester&)const = 0;
    private:
        static inline size_t enginesNum_ = 0;
        size_t id_;
};
class ICEngine: public Engine{
    public:
        virtual ~ICEngine() = default;
        virtual std::shared_ptr<EngineTestResult> accept(EngineTester& t)const{
            return t.testICEngine(*this);
        }
    ICEngine(double i, double c, double hm,
                                 double hv,
                                 double overheatTemp,
                                 std::function<double(double)> const&  velocityToRollingMoment):
                                                    i_(i),
                                                    c_(c),
                                                    hm_(hm),
                                                    hv_(hv),
                                                    overheatTemp_(overheatTemp),
                                                    velocityToRollingMoment_(velocityToRollingMoment)
    {
    }
    double getOverheatTemp()const{return overheatTemp_;}
    double getHm()const{return hm_;}
    double getHv()const{return hv_;}
    double getC()const{return c_;}
    double getI()const{return i_;}
    double velocityToRollingMoment(double m)const{return velocityToRollingMoment_(m);}
private:
    double i_;
    double c_;
    double hm_;
    double hv_;
    double overheatTemp_;
    std::function<double(double)> velocityToRollingMoment_;
};
