#include <vector>
#include <memory>
#include "Engine/Engine.h"
#include "EngineTester/EngineTestResult.h"
class TestStand{
public:
    TestStand(std::ostream& logger):
                        logger_(logger)
    {
    }
    void run() {
        for(auto& tester: testers_){
            for(auto& engine: engines_){
                logger_ << "_________________________________________________\n"
                        << tester->getType()<<" test started...\n"
                        << "Enigne id:  "<<engine->getId()<<"\n"
                        << *engine->accept(*tester)<<"\n"
                        <<"_________________________________________________\n\n";
            }
        }
    }
    void addEngine(std::unique_ptr<Engine> e){
        if(e){
            engines_.emplace_back(std::move(e));
        }
    }
    void addTester(std::unique_ptr<EngineTester> t){
        if(t){
            testers_.emplace_back(std::move(t));
        }
    }
private:
    std::ostream& logger_;
    std::vector<std::unique_ptr<EngineTester> > testers_;
    std::vector<std::unique_ptr<Engine> > engines_;
};
