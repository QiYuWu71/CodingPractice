#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;


class Expression{
    public:
        virtual string toString()const = 0;
        virtual ~Expression(){};
};

class NumExpression:public Expression{
    private:
        long number;
    public:
        NumExpression(long init_number){
            number = init_number;
        }
        string toString()const{
            stringstream ss;
            ss<<number;
            return ss.str();
        }
        virtual ~NumExpression(){};
};


class PlusExpression: public Expression{
    private:
        Expression *lhs;
        Expression *rhs;

    public:
        PlusExpression(Expression *init_lhs, Expression* init_rhs){
            lhs = init_lhs;
            rhs = init_rhs;
        };
        string toString()const{
            stringstream ss;
            ss<<"("<<lhs->toString()<<" + "<<rhs->toString()<<")";
            return ss.str();
        }
        virtual ~PlusExpression(){
            delete lhs;
            delete rhs;
        };
};