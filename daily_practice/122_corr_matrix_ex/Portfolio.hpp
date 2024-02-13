#include <vector>
#include <string>
#include "Asset.hpp"

#ifndef _PORTFOLIO_H_
#define _ASS_PORTFOLIO_H_ET_H_

class Portfolio {
private:
    std::vector<Asset> assets;

    double **covarianceMatrix;
    double **correlationMatrix;

    void computeCovarianceMatrix();
    double computeCovariance( long unsigned int a,  long unsigned int b);

public:
    Portfolio();
    ~Portfolio();

    void addAsset(std::string name);
    long unsigned int getNumberOfAssets();
    Asset &getAssetAt(int index);
    void computeCorrelationMatrix();
    void printCorrelationMatrix();
    void printAssetNames();
};

#endif
