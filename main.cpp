#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  //open file streams
  ifstream fin;

  string inputFile = argv[1];
  fin.open(inputFile);
  //-------------------------------
  if (!fin.is_open()) { 
    cout << "Error opening file: " << inputFile << endl;;
    return 1;
  }
  if (!(argc == 3) || !(argc == 4)){ 
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<< endl;
    return 1;
  }
  if ((argc == 4) && ((argv[3])!="--debug")){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<< endl;
    return 1;
  }
}