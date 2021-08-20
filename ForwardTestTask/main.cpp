#include <iostream>
#include "TestStand.h"
#include "PiecewiseLinear/PiecewiseLinearFunction.h"
int main(){
    auto& out = std::cout;
    auto& in = std::cin;
    TestStand testStand(out);
    out<<"Enter the environment temperature in celsium:\n";
    double environmentTemp;
    in>>environmentTemp;


    double i = 10.0;
    double c = 0.1;
    double hm = 0.001;
    double hv = 0.0001;
    double overheatTemp = 110.0;
    std::vector<double> m = {20, 75, 100, 105, 75, 0};
    std::vector<double> v = {0, 75, 150, 200, 250, 300};

    PiecewiseLinearFunction pl(v,m);
    ICEngine engine(i, c, hm, hv, overheatTemp, pl);
    EngineOverheatTester tester(environmentTemp, 0.001, 0.000001);

    testStand.addEngine(std::make_unique<ICEngine>(engine));
    testStand.addTester(std::make_unique<EngineOverheatTester>(tester));

    try{
          testStand.run();
    }catch(std::exception& e){
        std::cerr<<e.what()<<"\n";
    }
    return 0;
}
