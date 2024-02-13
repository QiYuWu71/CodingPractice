#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Portfolio.hpp"

using std::vector;
using std::string;

vector<string> parseLine(const string &line, const string &delim) {
    vector<string> result;
    
    auto start = 0U;
    auto end = line.find(delim);
    while (end != string::npos) {
        result.push_back(line.substr(start, end - start));
        start = end + delim.length();
        end = line.find(delim, start);
    }
    result.push_back(line.substr(start, end));
    
    return result;
}

std::ifstream openFile(std::string name) {
    std::ifstream in(name);
    if (!in.is_open()) {
        std::cerr << "Unable to open " << name << std::endl;
        exit(EXIT_FAILURE);
    }
    return in;
}

void parseFile(std::ifstream &in, Portfolio &myPortfolio) {
    string line;
    if (getline(in,line)) {
        vector<string> parts = parseLine(line,",");
        for (vector<string>::iterator it = parts.begin() + 1; it < parts.end(); it++ ) {
            myPortfolio.addAsset(*it);      
        }  
    }
    while (getline(in,line)) {
        vector<string> parts = parseLine(line,",");
        parts.erase(parts.begin()); // remove time sequence field
        if (parts.size()  != myPortfolio.getNumberOfAssets()) {
            std::cerr << "Invalid input line: " << line << std::endl;
            exit(EXIT_FAILURE);
        }
        for (long unsigned int i=0; i < parts.size(); i++) {
            myPortfolio.getAssetAt(i).addAssetPrice(parts[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " inputFile" << std::endl;
        return EXIT_FAILURE;
    }

    Portfolio myPortfolio;
    std::ifstream in = openFile(argv[1]);
    parseFile(in, myPortfolio);
    in.close();
    myPortfolio.computeCorrelationMatrix();
    myPortfolio.printAssetNames();
    myPortfolio.printCorrelationMatrix();

    return EXIT_SUCCESS;
}
