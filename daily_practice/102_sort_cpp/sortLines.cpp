#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void sortData(istream&in){
    string line;
    vector<string> lines;
    while (getline(in,line))
    {
        lines.push_back(line);
    }
   if ((in.eof()!=1)&&(in.good()!=1)){
       cerr << "Error in reading files."<< endl;
       exit (EXIT_FAILURE);
   }
    sort(lines.begin(),lines.end());
// code from docable files: StandardTemplateLibrary
    for (vector<string>::iterator it = lines.begin();
    it < lines.end();it++){
        cout << *it << endl;
    }
}
// code from docable files: Input and Output for C++
int main(int argc, char *argv[]){
    if (argc == 1){
        sortData(cin);
        }
    if (argc>1){
    for (int i = 1;i<argc; i++){
        ifstream in(argv[i]);
        if (!in.is_open()){
            cerr << "Unable to open"<< endl;
            exit(EXIT_FAILURE);
        }
        sortData(in);
        in.close();
        }
    }
    return EXIT_SUCCESS;
}