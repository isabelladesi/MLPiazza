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
  Classifier(bool debug_in) : totalPosts(0), uniqueWords(0), debug(debug_in){};

  void train(csvstream & trainStream){
    map<string, string> row;
    while(trainStream >> row){
      string words = row["content"];
      allWordSet = unique_words(words);
      // uniqueWords = uniqueWords + allWordSet.size();
      totalPosts++;
      label(row);
      word(row);
      labelWord(row);

      if(debug == true){
        cout << "label = " << row["tag"];
        cout << ", content = " << row["content"] << "\n";
      }
    }

    cout << "trained on " << totalPosts << " examples" << endl;
    if (debug == true){
      cout << "vocabulary size = " << words.size() << endl; 
    }
  }

  void completeLabels(){
    string label;
    int logScore;
    for (auto it = allWordSet.begin(); it!=allWordSet.end(); it++){
      label = correctlyLabel(*it);//input = singular post
      cout<< ", predicted = "<<label;
      logScore = predict(*it);
      cout<< "log-probability score = "<< logScore<<endl;
      cout<< "content = "<<*it;
      
    }
  }

  string correctlyLabel(string singularPost){ //a post
    double score;
    double maxScore;
    string correctLabel;
    for (int i=0; i <tags.size(); ++i){ //for each label
      score = predict(labels[i]);
      if (score > maxScore){
        maxScore = score;
        correctLabel = labels[i];
      }
      score = 0;
    }
    return  correctLabel;
  }
  //prediction (math) (parameters: a label, string ofwords in new post)
  double predict(string label) { 
    //gives unique words string. words=long string that holds posts content
    set<string> uniqueWords = unique_words(word1);  
    //auto it = uniqueWords.begin();
    vector<string> allWords;
    int j=0;
    for (auto it = uniqueWords.begin(); it!=uniqueWords.end(); it++){
      allWords[j] = *it;
      j++;
    }

    double prediction = 0;

    //log prior
    double logPrior;
    int numCTrainP = tags[label];    //number of training posts with label C tags[,]
    int numTrainPosts = totalPosts;       // number of training posts
    logPrior = log(numCTrainP/numTrainPosts);
    prediction += logPrior;

    for(int i=0; i<uniqueWords.size(); ++i){// each unique word
      map<string,int> innerMap = tagsWords[label];
      //=function that says how many times word appears in the traininposts 
      //with label C ...[i];  number of training posts with label C that contain W
      int numCTrainPW = innerMap[allWords[i]];
      //=function that says how many times word appears in all 
      //training posts regardless of label
      int numTrainPW = words[allWords[i]];
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
  // int posts;
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
  map<string, map<string,int>> tagsWords; //label word int
  map<string, int> words;
  vector<string> labels; //set
  int totalPosts;
  int uniqueWords;
  bool debug;
  set<string> allWordSet;
  //checks number of labels
  void label(map<string, string> & row){
    string tag = row["tag"];
    if(tags.find(tag)!= tags.end()){
      tags[tag] += 1;
    }
    else{
      tags.insert({tag, 1});
    }
  }

  //checks number of words
  string word1; //string of content
  void word(map<string, string> & row){
    word1 = row["content"];
    set<string> wordSet = unique_words(word1);
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
  cout.precision(3);
  //open file streams
  string trainF = argv[1];
  string testF = argv[2];
  string debugS = argv[3];
  bool debugBool = false;
  csvstream trainFile = csvstream(trainF);
  csvstream testFile = csvstream(testF);
    //-------------------------------
  if (!(argc == 3) && !(argc == 4)){ 
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<< endl;
    return 1;
  }
  if ((argc == 4) && (!(debugS=="--debug"))){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<< endl;
    return 1;
  }
  if(argc == 4){
    debugBool = true;
    cout << "training data:" << "\n";
  }
  Classifier mainClass(debugBool);
  mainClass.train(trainFile);
}