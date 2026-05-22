using namespace std;
#include <iostream>
#include <string>
class FlashCard {
private:
    string question;
    string answer;

public:
    FlashCard() {
        question = "";
        answer = "";
    }

    FlashCard(string q, string a) {
        question = q;
        answer = a;
    }

    void setQuestion(string q) {
        question = q;
    }

    void setAnswer(string a) {
        answer = a;
    }

    string getQuestion() const {
        return question;
    }

    string getAnswer() const {
        return answer;
    }
};