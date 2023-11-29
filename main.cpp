#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "csvstream.hpp"
using namespace std;

class Classifier{
  public:
  train(csvstream & trainStream, bool debug){
    map<string, string> row;
    string label;
    while(trainStream >> row){
      label = row["tag"];
      if(tags.find(label)!= tags.end()){
        tags[label] += 1;
      }
      else{
        tags.insert({label, 1});
      }
    }
  }
  test(csvstream &);

  private:
  //training steps
  map<string, int> tags;
  map<string, int> tagsWithWords; //not right
  map<string, int> words;
  // The total number of posts in the entire training set.
  // The number of unique words in the entire training set. (The vocabulary size.)
  // For each word the number of posts in the entire training set that contain 
  // For each label the number of posts with that label.
  // For each label and word , the number of posts with label that contain 

  // EFFECTS: Return a set of unique whitespace delimited words.x
  set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
      words.insert(word);
    }
    return words;
  }
};
int main(int argc, char **argv) {
  //open file streams
  string inputFile = argv[1];
  string testFile = argv[2];

  try{
    csvstream input = csvstream(inputFile);
    csvstream test = csvstream(testFile);
  } catch(const csvstream_exception &e){
    cout << e.what();
  }
  //-------------------------------
  if (!(argc == 3) || !(argc == 4)){ 
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<< endl;
    return 1;
  }
  if ((argc == 4) && ((argv[3])!="--debug")){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<< endl;
    return 1;
  }
}