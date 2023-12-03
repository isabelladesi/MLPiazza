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

  string correctlyLabel(csvstream & singularPost){ //a post
    double score;
    double maxScore;
    string correctLabel;
    for (int i=0; i <tags.size(); ++i){ //for each label
      score = predict(labels[i], singularPost);
      if (score > maxScore){
        maxScore = score;
        correctLabel = labels[i];
      }
      score = 0;
    }
    return  correctLabel;
  }
  //prediction (math) (parameters: a label, string ofwords in new post)
  double predict(string label, csvstream & testStream) { 
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
  string inputFile = argv[1];
  string testFile = argv[2];
  string debug = argv[3];
  
  try{
    csvstream input = csvstream(inputFile);
    csvstream test = csvstream(testFile);

    vector<pair<string, string>> row;
    // map<string, string> row;
    if(argc == 4){
      cout << "training data:" << "\n";
      
        while (input >> row) {
        // Print the third and fourth columns
          for (unsigned int i = 2; i < row.size() && i < 4; ++i) {
            // const string &column_name = row[i].first;
            const string &datum = row[i].second;
            if(i==2){
              cout << "  label = " << datum;
            }
            if(i==3){
              cout << ", content = " << datum << "\n";
            }
          }
        }
    }
  } catch(const csvstream_exception &e){
    cout << e.what();
  }

    //-------------------------------
  if (!(argc == 3) || !(argc == 4)){ 
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<< endl;
    return 1;
  }
  if ((argc == 4) && (!(debug=="--debug"))){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<< endl;
    return 1;
  }
  // how do you read each specific post in the file.

  // string label;
  // int logScore;
  //for(int i=0; i<(num of posts in file) < ++i){
    // label = correctlyLabel(input);//input = singular post
    // cout<< ", predicted = "<<label;
    // logScore = predict(input);
    // cout<< "log-probability score = "<< logScore<<endl;
    // cout<< "content = "<<input;
  // }
}