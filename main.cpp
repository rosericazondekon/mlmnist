#include "dataproc.h"
#include <iostream>

int main() {
    DataHandler *dh = new DataHandler();
    dh->loadFeatureVector("./mnist_data/train-images.idx3-ubyte");
    dh->loadLabels("./mnist_data/train-labels.idx1-ubyte");
    dh->countClasses();
    dh->splitDataset();

    // Example: Print out the first 5 labels from the dataset
    auto dataset = dh->getDataset();
    for (size_t i = 0; i < 5 && i < dataset->size(); i++) {
        std::cout << "Label " << (int)(*dataset)[i]->getLabel() << " exists! Class = " << (*dataset)[i]->getEnumLabel() << std::endl;
    }

    return 0;
}