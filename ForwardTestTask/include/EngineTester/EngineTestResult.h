#pragma once
#include <iostream>
#include <memory>
class EngineTestResult{
public:
    friend std::ostream& operator <<(std::ostream& out, EngineTestResult const& res);
protected:
    virtual void print(std::ostream& out)const = 0;
};
inline std::ostream& operator<<(std::ostream& out, EngineTestResult const& res){
    res.print(out);
    return out;
}

class NegativeOverheatTestResult;
class PositiveOverheatTestResult;
class OverheatTestResult: public EngineTestResult{
public:
      OverheatTestResult(bool testPassed):
                        testPassed_(testPassed)
      {
      }
      static std::shared_ptr<NegativeOverheatTestResult> negative(double temperature){
            return std::make_shared<NegativeOverheatTestResult>(temperature);
      }
      static std::shared_ptr<PositiveOverheatTestResult> positive(double temperature){
            return std::make_shared<PositiveOverheatTestResult>(temperature);
      }
protected:
      virtual void print(std::ostream& out)const{
            if(testPassed_){
                out<<"Test passed!";
            }else{
                out<<"Test failed!";
            }
      }
private:
    bool testPassed_;
};
class PositiveOverheatTestResult: public OverheatTestResult{
public:
    PositiveOverheatTestResult(double overheatTime):
                                        OverheatTestResult(false),
                                        overheatTime_(overheatTime)

    {
    }
protected:
    void print(std::ostream& out)const{
        OverheatTestResult::print(out);
        out<<" Overheat in "<<overheatTime_<<" second(s).";
    }
private:
    double overheatTime_;
};
class NegativeOverheatTestResult: public OverheatTestResult{
public:
    NegativeOverheatTestResult(double temperature):
                                    OverheatTestResult(true),
                                    temperature_(temperature)
    {
    }
protected:
    void print(std::ostream& out)const{
        OverheatTestResult::print(out);
        out<<" Temperature stabilized at "<<temperature_<<" celsium degrees.";
    }
private:
    double temperature_;
};
