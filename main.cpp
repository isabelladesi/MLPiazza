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
  Classifier(bool debug_in) : totalPosts(0), debug(debug_in){};

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
        cout << "  label = " << row["tag"];
        cout << ", content = " << row["content"] << "\n";
      }
    }

    cout << "trained on " << totalPosts << " examples" << endl;
    if (debug == true){
      cout << "vocabulary size = " << words.size() << endl;
      cout<<endl;

      cout << "classes:" << endl;
      for (const auto& pair : tags) {
        cout << "  " << pair.first << ", " << pair.second 
          << " examples, log-prior = " << log_prior(pair.first, pair.second, totalPosts)<< endl;
      }

      cout << "classifier parameters:" << endl;
      for (const auto& outerMap : tagsWords) {
        const string& outerTag = outerMap.first; //label
        const map<string, int>& innerMap = outerMap.second; //word,int (how many times word appears under label)
        // Iterate through the inner map
        for (const auto& innerMap : innerMap) {
            const string& innerWord = innerMap.first; //word
            int innerValue = innerMap.second; //int
            cout << "  " << outerTag << ":" << innerWord << ", count = " 
              << innerValue << ", log-likelihood = " << log_liklihood(outerTag, innerValue, words[innerWord], tags[outerTag])<< endl;
        }
      }
    }
  }

  void completeLabels(csvstream & testStream){
    cout<<endl;
    cout<<"test data:"<<endl;
    map<string, string> row;
    while(testStream >> row){
      string testWords = row["content"];
      allWordSet = unique_words(testWords);
      cout << "  correct = " << row["tag"];
      string label;
      int logScore;
     // for (auto it = allWordSet.begin(); it!=allWordSet.end(); it++){ //goes thorugh each word in content
        label = correctlyLabel(testWords);//input = singular post
        cout<< ", predicted = "<<label;
        logScore = predict(label, testWords);
        cout<< "log-probability score = "<< logScore<<endl;
        cout<< " content = "<<testWords<<endl;
        cout<<endl;
     // }
    }
    cout << "performance: "<<" / "<< "posts predicted correctly"<<endl;
  }

  string correctlyLabel(string singularPost){ //a post
    double score;
    double maxScore;
    string correctLabel;
    for (const auto& pair : tags) { //for each label
      score = predict(pair.first , singularPost);
      if (score > maxScore){
        maxScore = score;
        correctLabel = pair.first;
      }
      score = 0;      
      }
    // for (int i=0; i <tags.size(); ++i){ //for each label
    //   score = predict(labels[i]);
    //   if (score > maxScore){
    //     maxScore = score;
    //     correctLabel = labels[i];
    //   }
    //   score = 0;
    // }
    return  correctLabel;
  }
  //prediction (math) (parameters: a label, string ofwords in new post)
  double log_prior(string label, double numTrainWC, double totTrainPosts){
    double log_Prior=0;
    double div = numTrainWC/totTrainPosts;
    log_Prior = log(div);
    return log_Prior;
  }
  double log_liklihood(string label,double numCTrainPostsWithW, double numTrainPostswithW, double numTrainPWithC){
    double logLiklihood=0;
    if(numCTrainPostsWithW==0 && numTrainPostswithW!=0){ //special case 1
        double div1 = numTrainPostswithW/totalPosts;
        logLiklihood = log(div1);
      }
      else if(numCTrainPostsWithW==0 && numTrainPostswithW==0){
        double div2 = 1.0/totalPosts;
        logLiklihood = log(div2);
      }
      else{
        double div = numCTrainPostsWithW/numTrainPWithC;
        logLiklihood = log(div);
      }
      return logLiklihood;
  }

  double predict(string label, string postContent) { 
    //gives unique words string. words=long string that holds posts content
    set<string> uniqueWords = unique_words(postContent);  //all unique words in content of deisignated post
    //auto it = uniqueWords.begin();
    // vector<string> allWords;
    // int j=0;
    // for (auto it = uniqueWords.begin(); it!=uniqueWords.end(); it++){
    //   allWords[j] = *it;
    //   j++;
    // }

    double prediction = 0;

    //log prior
    double numCTrainP = tags[label];    //number of training posts with label C tags[,]
    double numTrainPosts = totalPosts;       // number of training posts
    double logPrior = log_prior(label, numCTrainP, numTrainPosts);
    prediction += logPrior;
    // int i=0;
    // while(i<uniqueWords.size()){ //each unique word in the designated post
    // for(int i=0; i<uniqueWords.size(); ++i){// each unique word
      map<string,int> innerMap = tagsWords[label]; //how many times word appears in that label
      for (auto it = uniqueWords.begin(); it != uniqueWords.end(); ++it) {
        //=function that says how many times word appears in the traininposts 
        //with label C ...[i];  number of training posts with label C that contain W
        double numCTrainPW = innerMap[*it];//it->first];
        //=function that says how many times word appears in all 
        //training posts regardless of label
        double numTrainPW = words[*it];//it->first];
        //log liklihood
        double logLikl = 0;
        logLikl = log_liklihood(label,numCTrainPW, numTrainPW, numCTrainP);
        
        prediction += logLikl;
        logLikl=0;
      }
    //   i++;
    // }
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
  map<string, map<string,int>> tagsWords; //label word int(how many times word appears in that label)
  map<string, int> words;
  vector<string> labels; //set
  int totalPosts;
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
          tagsWords[tag][*it] += 1;
        }
        else{
          tagsWords[tag][*it]=1;
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
  mainClass.completeLabels(testFile);
}