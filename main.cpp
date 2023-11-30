#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "csvstream.hpp"
using namespace std;

class Classifier{
  public:
  void train(csvstream & trainStream, bool debug){
    label(trainStream);
    word(trainStream);
    labelWord(trainStream);
  }
  void test(csvstream & testStream);

  private:
  //training steps
  int posts;
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
  map<string, int> tags;
  map<string, map<string,int>> tagsWords; //not right
  map<string, int> words;
  //checks number of labels
  void label(csvstream & trainStream){
    map<string, string> row;
    string tag;
    while(trainStream >> row){
      tag = row["tag"];
      if(tags.find(tag)!= tags.end()){
        tags[tag] += 1;
      }
      else{
        tags.insert({tag, 1});
      }
    }
  }
  //checks number of words
  void word(csvstream & trainStream){
    map<string, string> row;
    string word;
    while(trainStream >> row){
      word = row["content"];
      set<string> wordSet = unique_words(word);
      for (auto it = wordSet.begin(); it != wordSet.end(); ++it) {
        if(words.find(*it)!= words.end()){
          words[*it] += 1;
        }
        else{
          words.insert({*it, 1});
        }
      }
    }
  }
  //checks labels and words
  void labelWord(csvstream & trainStream){
    map<string, string> row;
    string tag;
    string word;
    string tagWord;
    while(trainStream >> row){
      tag = row["tag"];
      word = row["content"];
      set<string> wordSet = unique_words(word);
      for (auto it = wordSet.begin(); it != wordSet.end(); ++it) {
        if((words.find(*it)!= words.end()) && (tags.find(tag)!= tags.end())){
          tagsWords[tag][word] += 1;
        }
        else{
          tagsWords.insert({tag,{word, 1}}); //figure out syntax
        }
      }
    }
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