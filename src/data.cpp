#include "data.h"

Data::Data()
{
    feature_vector = new std::vector<uint8_t>();
}

Data::~Data()
{
    if(feature_vector) {
        delete feature_vector;
    }
}

void Data::setFeatureVector(std::vector<uint8_t>* vect)
{
    feature_vector = vect;
}

void Data::appendToFeatureVector(uint8_t value)
{
    feature_vector->push_back(value);
}

void Data::setLabel(uint8_t value)
{
    label = value;
}

void Data::setEnumLabel(int value)
{
    enum_label = value;
}

int Data::getFeatureVectorSize()
{
    return feature_vector->size();
}

uint8_t Data::getLabel()
{
    return label;
}

int Data::getEnumLabel()
{
    return enum_label;
}

std::vector<uint8_t>* Data::getFeatureVector()
{
    return feature_vector;
}