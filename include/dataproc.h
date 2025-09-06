#ifndef DATAPROC_H
#define DATAPROC_H

#include <fstream>
#include "stdint.h"
#include "data.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

class DataHandler {
public:
    DataHandler();
    ~DataHandler();

    void loadFeatureVector(const std::string &);
    void loadLabels(const std::string &);
    void splitDataset();
    void countClasses();
    uint32_t swapToLittleEndian(const unsigned char*);
    std::vector<Data*>* getDataset();
    std::vector<Data*>* getTrainset();
    std::vector<Data*>* getTestset();
    std::vector<Data*>* getValidationset();

private:
    std::vector<Data*> *_dataset;
    std::vector<Data*> *_trainset;
    std::vector<Data*> *_testset;
    std::vector<Data*> *_validationset;
    int numClasses;
    int featureVectorSize;
    std::map<uint8_t, int> classMap;
    const double TRAIN_SPLIT = 0.75;
    const double VALIDATION_SPLIT = 0.05;
    const double TEST_SPLIT = 0.2;
};

#endif // DATAPROC_H