#ifndef DATA_H
#define DATA_H

#include <vector>
#include "stdint.h"
#include "stdio.h"

class Data {
public:
    Data();
    ~Data();
    void setFeatureVector(std::vector<uint8_t>*);
    void appendToFeatureVector(uint8_t);
    void setLabel(uint8_t);
    void setEnumLabel(int);

    int getFeatureVectorSize();
    uint8_t getLabel();
    int getEnumLabel();
    std::vector<uint8_t>* getFeatureVector();

private:
    std::vector<uint8_t>* feature_vector;
    uint8_t label;
    int enum_label;
};

#endif // DATA_H