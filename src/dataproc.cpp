#include <iostream>
#include "dataproc.h"
#include <numeric>
#include <random>

DataHandler::DataHandler()
{
    _dataset = new std::vector<Data*>();
    _trainset = new std::vector<Data*>();
    _testset = new std::vector<Data*>();
    _validationset = new std::vector<Data*>();
}
DataHandler::~DataHandler()
{
    for(auto data : *_dataset) {
        delete data;
    }
    delete _dataset;
    delete _trainset;
    delete _testset;
    delete _validationset;
}

void DataHandler::loadFeatureVector(const std::string & path)
{
    uint32_t header[4]; // magic number, number of images, row size, column size
    unsigned char bytes[4];

    FILE *file = fopen(path.c_str(), "r");
    if(file)
    {
        // Read the header information
        for(size_t i = 0; i < 4; i++) {
            if(fread(bytes, sizeof(bytes), 1, file))
            {
                header[i] = swapToLittleEndian(bytes);
            }
            
        }
        std::cout << "Done getting file header..." << std::endl
                  << "      Magic Number: " << header[0] << std::endl
                  << "      Number of Images: " << header[1] << std::endl
                  << "      Row Size: " << header[2] << std::endl
                  << "      Column Size: " << header[3] << std::endl;

        featureVectorSize = header[2] * header[3]; // rows * cols

        // Read the feature vectors
        for(size_t i = 0; i < header[1]; i++) { // number of images
            Data* data = new Data();

            for(size_t j = 0; j < featureVectorSize; j++) {
                uint8_t pixel = 0;
                if(fread(&pixel, sizeof(uint8_t), 1, file))
                {
                    data->appendToFeatureVector(pixel);
                }
                else
                {
                    std::cerr << "Error reading feature vector data." << std::endl;
                    exit(1);
                }
            }
            _dataset->push_back(data);
        }
        fclose(file);
        std::cout << "Done loading feature vectors size " << _dataset->size() << std::endl;
    } else {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(1);
    }
}
void DataHandler::loadLabels(const std::string & path)
{
    uint32_t header[2]; // magic number, number of items
    unsigned char bytes[4];

    FILE *file = fopen(path.c_str(), "r");
    if(file)
    {
        // Read the header information
        for(size_t i = 0; i < 2; i++) {
            if(fread(bytes, sizeof(bytes), 1, file))
            {
                header[i] = swapToLittleEndian(bytes);
            }
        }
        std::cout << "Done getting label file header..." << std::endl
                  << "      Magic Number: " << header[0] << std::endl
                  << "      Number of Items: " << header[1] << std::endl;

        if(header[1] != _dataset->size()) {
            std::cerr << "Number of labels does not match number of feature vectors." << std::endl;
            exit(1);
        }

        // Read the labels
        for(size_t i = 0; i < header[1]; i++) { // number of items
            uint8_t label = 0;
            if(fread(&label, sizeof(uint8_t), 1, file))
            {
                (*_dataset)[i]->setLabel(label);
            }
            else
            {
                std::cerr << "Error reading label data." << std::endl;
                exit(1);
            }
        }
        fclose(file);
        std::cout << "Done loading labels." << std::endl;
    } else {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(1);
    }
}

void DataHandler::splitDataset()
{
    int trainSize = _dataset->size() * TRAIN_SPLIT;
    int validationSize = _dataset->size() * VALIDATION_SPLIT;
    int testSize = _dataset->size() * TEST_SPLIT;

    // Create a copy of dataset indices and shuffle them
    std::vector<size_t> indices(_dataset->size());
    std::iota(indices.begin(), indices.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    // Split the shuffled indices into train, validation and test sets
    for (size_t i = 0; i < indices.size(); i++) {
        if (i < trainSize) {
            _trainset->push_back((*_dataset)[indices[i]]);
        } else if (i < trainSize + validationSize) {
            _validationset->push_back((*_dataset)[indices[i]]);
        } else {
            _testset->push_back((*_dataset)[indices[i]]);
        }
    }

    std::cout << "Dataset split into:" << std::endl
              << "  Training set size: " << _trainset->size() << std::endl
              << "  Test set size: " << _testset->size() << std::endl
              << "  Validation set size: " << _validationset->size() << std::endl;
}

void DataHandler::countClasses()
{
    int count = 0;
    for(size_t i = 0; i < _dataset->size(); i++) {
        uint8_t label = (*_dataset)[i]->getLabel();
        if(classMap.find(label) == classMap.end()) {
            classMap[label] = count;
            (*_dataset)[i]->setEnumLabel(count);
            count++;
        } else {
            (*_dataset)[i]->setEnumLabel(classMap[label]);
        }
    }
    numClasses = count;
    std::cout << "Successfully extracted number of unique classes: " << numClasses << std::endl;
}

uint32_t DataHandler::swapToLittleEndian(const unsigned char* bytes)
{
    return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8) | (uint32_t)bytes[3];
}

std::vector<Data*>* DataHandler::getDataset()
{
    return _dataset;
}

std::vector<Data*>* DataHandler::getTrainset()
{
    return _trainset;
}

std::vector<Data*>* DataHandler::getTestset()
{
    return _testset;

}
std::vector<Data*>* DataHandler::getValidationset()
{
    return _validationset;
}
