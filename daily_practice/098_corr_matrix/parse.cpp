# include "asset.hpp"
#include <cstdio>
#include <iomanip>

// determine asset name: code with correction from docable file "C++ string";
vector<string> asset_name(string headerr){
    vector<string> name_vec;
    string delim = ",";

    auto start = 0U;
    auto end = headerr.find(delim);
    while (end != string::npos){
        name_vec.push_back(headerr.substr(start,end-start));
        start = end+delim.length();
        end = headerr.find(delim,start);
    }
    name_vec.push_back(headerr.substr(start,end));
    if (name_vec.size() == 0){
        fprintf(stderr,"Error in header: do not use the comma; Or only one item in the header");
        exit(EXIT_FAILURE);
    }
    return name_vec;
}

//store asset prices into vector string;
vector<double> asset_price(string line,vector<double> last_price,int flag){
    vector<double> price_vec;
    string delim = ",";
    auto start = 0U;
    auto end = line.find(delim);
    int loc = 0;
    while (end != string::npos){
        if (loc != 0){
        string price;
        price = line.substr(start,end-start);
        try{
            double d = stod(price);
            price_vec.push_back(d);
        }catch(const invalid_argument&){
            if (flag == 1){
            cerr << "Invalid argument: " << price<< endl;
            exit(EXIT_FAILURE);
            }else{
                price_vec.push_back(last_price[loc-1]);
            }
        }catch(out_of_range&){
            if (flag == 1){
            cerr << "out of range of double: " << price << endl;
            exit(EXIT_FAILURE);
            }else{
                price_vec.push_back(last_price[loc-1]);
            }
        }}
        start = end + delim.length();
        end = line.find(delim,start);
        loc ++;

    }

    string price;
    price = line.substr(start,end);
    try{
        double d = stod(price);
        price_vec.push_back(d);
    }catch(const invalid_argument&){
        if (flag == 1){
        cerr << "Invalid argument: " << price<< endl;
        exit(EXIT_FAILURE);
        }else{
            price_vec.push_back(last_price[loc-1]);
        }
    }catch(out_of_range&){
        if (flag == 1){
        cerr << "out of range of double: " << price << endl;
        exit(EXIT_FAILURE);
        }else{
            price_vec.push_back(last_price[loc-1]);
        }
        }
    if (last_price.size()!=price_vec.size()){
        cerr << "Lack number in the dataset." << endl;
        exit(EXIT_FAILURE);
    }
    return price_vec;
}

// calculate rate of return vectors
vector<double> asset_ror(vector<double> price_vec){
    vector<double> aror;
    for (size_t i = 0; i<price_vec.size();i++){
        if (i==0){
            aror.push_back(0);
        }
        else{
            aror.push_back((price_vec[i]/price_vec[i-1])-1);
        }
    }
    return aror;
}

void print_matrix(Matrix mat){
    cout<<setprecision(4)<<fixed;
    cout<<"[";
    for (size_t i = 0; i<mat.getRows();i++){
        for (size_t j = 0; j < mat.getColumns();j++){
            cout<<mat[i][j];
            if (j!=mat.getColumns()-1){
                cout<<", ";
            }
        }
        if (i!=mat.getRows()-1){
            cout<<"\n";
        }}
    cout<<" ]";

}


void parse(istream&ifs){
    std::string line;
    vector<string> lines;
    while(getline(ifs,line)){
        lines.push_back(line);
    }
   if ((ifs.eof()!=1)&&(ifs.good()!=1)){
        fprintf(stderr,"Error in reading files.\n");
        exit(EXIT_FAILURE);
   }
    string headerr;
    headerr = lines[0];
    vector<string> name_vec;
    name_vec = asset_name(headerr);
    // record asset prices and cal rate of return;
    size_t nrow = name_vec.size()-1;
    size_t ncol = lines.size()-1;
    Matrix prices(ncol,nrow); // prices and time matrix;
// keep tracking of price records
// deal with the special line one;
    vector<double> last_price;
    vector<double> price_vec;
    for (size_t i = 0;i<nrow;i++){
        last_price.push_back(0);
    }
    for(size_t i = 1; i<ncol+1;i++){
        price_vec = asset_price(lines[i],last_price,i);
        for (size_t j = 0; j<nrow;j++){
            prices[j][i-1] = price_vec[j];
        }
        last_price = price_vec;
    }

// create covariance and denom; 
    Matrix Corr(nrow,nrow);
    vector<Asset *> portfolio;
    for (size_t i =0;i<nrow;i++){
        vector<double> aror = asset_ror(prices[i]);
        Asset *index = new Asset(name_vec[i+1],aror);
        index->avg_ror();
        index->sd_ror();
        index->print_asset();
        portfolio.push_back(index);
    }

    for (size_t i=0;i<nrow;i++){
        for (size_t j = i;j < nrow;j++){
            if (i==j){
                Corr[i][j] = 1;
            }
            else{
            Asset *porti = portfolio[i];
            Asset *portj = portfolio[j];
            Corr[i][j] = porti->corr_ror(*portj);
            Corr[j][i] = Corr[i][j];}
        }
    }
    cout<<Corr<<endl;

    for (size_t i=0; i<nrow;i++){
        delete portfolio[i];
    }

}