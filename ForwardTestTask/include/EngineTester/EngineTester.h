#pragma once
#include <iostream>
#include <memory>
class Engine;
class ICEngine;
class EngineTestResult;

class EngineTester{
public:
    virtual ~EngineTester() = default;
    virtual std::shared_ptr<EngineTestResult> testICEngine(ICEngine const&) = 0;
    virtual std::string getType() const = 0;
};

class EngineOverheatTester: public EngineTester{
public:
    EngineOverheatTester(double environmentTemp,double timeStep, double minimalTempStep):
                            environmentTemp_(environmentTemp),
                            timeStep_(timeStep),
                            minimalTempStep_(minimalTempStep)
    {
    }
    virtual std::shared_ptr<EngineTestResult> testICEngine(ICEngine const&);
    virtual std::string getType()const override{return "Overheat";}
private:
    double const environmentTemp_;
    double const timeStep_;
    double const minimalTempStep_;
};
