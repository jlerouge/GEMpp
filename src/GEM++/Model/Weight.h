#ifndef GEMPP_WEIGHT_H
#define GEMPP_WEIGHT_H

#include "../Core/Printer.h"

class DLL_EXPORT Weight {
    public:
        enum Type{
            CONSTANT = 0,
            DISCRETE,
            NUMERIC,
            STRING,
            COUNT
        };

        static const char* typeName[COUNT];
        static Type fromName(QString typeName);
        static QString toName(Type type);

        Weight(Type type, uint power, double value);
        Weight(Weight &other);
        ~Weight();

        Type getType() const;
        Type &type();
        void setType(Type type);

        uint getPower() const;
        uint &power();
        void setPower(uint power);

        double getValue() const;
        double &value();
        void setValue(double value);

    private:
        Type type_;
        uint power_;
        double value_;
};
#endif /*WEIGHT_H*/
