#include "EngineTester/EngineTester.h"
#include "EngineTester/EngineTestResult.h"
#include "Engine/Engine.h"

std::shared_ptr<EngineTestResult>
EngineOverheatTester::testICEngine(ICEngine const& e){
    double overheatTemp = e.getOverheatTemp();
    double i = e.getI();
    double hm = e.getHm();
    double hv = e.getHv();
    double c = e.getC();

    double engineTemp = environmentTemp_;
    double time = 0.0;
    double v = 0.0;

    while (engineTemp < overheatTemp){
        double m = e.velocityToRollingMoment(v);
        v += m * timeStep_ / i;
        double vh = m * hm + v * v * hv;
        double vc = c * (environmentTemp_ - engineTemp);
        time += timeStep_;
        double temperatureStep = timeStep_* (vh + vc);
        engineTemp += temperatureStep;
        if (temperatureStep <= minimalTempStep_) {
            return OverheatTestResult::negative(engineTemp);
        }
    }
    return OverheatTestResult::positive(time);
}
