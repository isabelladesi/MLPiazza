#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include "csvstream.hpp"
using namespace std;

class Classifier{
  public:
  void train(csvstream & trainStream, bool debug){
    map<string, string> row;
    while(trainStream >> row){
      label(row);
      word(row);
      labelWord(row);
    }
  }

  string test(csvstream & testStream){
    double score;
    double maxScore;
    for (int i=0; i <tags.size(); ++i){
      score = predict(labels[i], testStream);
      if (score > maxScore){
        maxScore = score;
      }
      score = 0;
    }
    return  label;
  }
  double predict(string label, csvstream & testStream) { //prediction (math) (parameters: a label, string ofwords in new post)
    set<string> uniqueWords = unique_words(testStream); //gives unique words string

    double prediction = 0;

    //log prior
    double logPrior;
    int numCTrainP = tags[label];    //number of training posts with label C tags[,]
    int numTrainPosts = totalPosts;       // number of training posts
    logPrior = log(numCTrainP/numTrainPosts);
    prediction += logPrior;

    for(int i=0; i<uniqueWords.size(); ++i){// each unique word
      int numCTrainPW = tagsWords[label, uniqueWords[i]]// =function that says how many times word appears in the traininposts with label C ...[i]; //number of training posts with label C that contain W
      int numTrainPW = //=function that says how many times word appears in all training posts regardless of label
      
      //log liklihood
      double logLikl = 0;
      if(numCTrainPW==0 && numTrainPW!=0){ //special case 1
        logLikl = log(numTrainPW/numTrainPosts);
      }
      else if(numCTrainPW==0 && numTrainPW==0){
        logLikl = log(1/numTrainPosts);

      }
      else{
        logLikl = log(numCTrainPW/numCTrainP);
      }

      prediction += logLikl;
      logLikl=0;

    }
    return prediction; //will return prediction score for a particular label
    // for each label find its score using equation
    // the classifier will pick the label with the highest score
    // there should be n log likelihood terms. n = number of UNIQUE words in string (post)
    //in divisions: cast the numer and denom as double before 

  }

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
  vector<string> labels; //set
  int totalPosts=0;
  //checks number of labels
  void label(map<string, string> & row){
    string tag = row["tag"];
    if(tags.find(tag)!= tags.end()){
      tags[tag] += 1;
      totalPosts++;
    }
    else{
      tags.insert({tag, 1});
    }
  }
  //checks number of words
  void word(map<string, string> & row){
    string word;
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

  //checks labels and words
  void labelWord(map<string, string> & row){
    string tag;
    string word;
    string tagWord;
    tag = row["tag"];
    word = row["content"];
    set<string> wordSet = unique_words(word);
      for (auto it = wordSet.begin(); it != wordSet.end(); ++it) {
        if((words.find(*it)!= words.end()) && (tags.find(tag)!= tags.end())){
          tagsWords[tag][word] += 1;
        }
        else{
          tagsWords[tag][word]=1;
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