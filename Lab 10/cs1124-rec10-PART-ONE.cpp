
#include <iostream>
#include <vector>
using namespace std;

class Instrument{
public:
    virtual void makeSound() const = 0;
};

class Brass: public Instrument{
public:
    Brass(int mouthpiece): mouthpiece(mouthpiece){}
    void makeSound() const{
        cout << "To make a sound... blow on a mouthpiece of size " << mouthpiece << endl;
    }
private:
    int mouthpiece;
};

class String: public Instrument{
public:
    String(int pitch): pitch(pitch){}
    void makeSound() const{
        cout << "To make a sound... bow a string with pitch " << pitch << endl;
    }
private:
    int pitch;
};

class Percussion: public Instrument{
public:
    void makeSound() const{
        cout << "To make a sound... hit me!" << endl;
    }
private:
};

class Musician {
public:
    Musician() : instr(nullptr) {}
    void acceptInstr(Instrument& i) { instr = &i; }
    Instrument* giveBackInstr() { 
        Instrument* tmp(instr); 
        instr = nullptr;
        return tmp;
    }
    void testPlay() const {
        if(instr)
            instr->makeSound(); 
        else
            cerr << "have no instr\n";
    }
private:
    Instrument* instr;
};

class MILL{
public:
    void receiveInstr(Instrument& instrument){
        for (Instrument* i: instruments){
            if (!i){
                i = &instrument;
                return;
            }
        }
        instruments.push_back(&instrument);
    }
    void dailyTestPlay() const{
        for (Instrument* i: instruments){
            if(i){
                i->makeSound();
                
        }
    }
    Instrument* loanOut() {
        for (int i = 0; i < instruments.size(); ++i){
            if(instruments[i]){
                Instrument* ret = instruments[i];
                instruments[i] = nullptr;
                return ret;
            }
        }
        return nullptr;
    }
    void giveBackInstr(Instrument& instrument){
        receiveInstr(instrument);
    }
private:
    vector<Instrument*> instruments;
};

// PART ONE
int main() {

    cout << "Define some instruments ----------------------------------------\n";
    Percussion drum;
    String cello(673);
    Percussion cymbal;
    Brass tbone(4);
    Brass trpt(12) ;
    String violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL ------------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -----------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians-------------------------------------------\n";
    Musician j;
    Musician jj;
    Musician q;
  	
    cout << "TESTING: q.acceptInstr(*mill.loanOut());-----------------------\n";
    q.testPlay();	
    cout << endl;
    q.acceptInstr(*mill.loanOut());
    cout << endl;
    q.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    q.testPlay();	
    cout << endl;
    mill.receiveInstr(*q.giveBackInstr());
    j.acceptInstr(*mill.loanOut());
    q.acceptInstr(*mill.loanOut());
    cout << endl;
    q.testPlay();
    cout << endl;
    j.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    // cout << "TESTING: mill.receiveInstr(*q.giveBackInstr()); -------------\n";
  
    // // fifth
    // mill.receiveInstr(*q.giveBackInstr());
    // cout << "TESTING: mill.receiveInstr(*j.giveBackInstr()); -------------\n";
    // mill.receiveInstr(*j.giveBackInstr());

  
    // cout << endl;
    // cout << "dailyTestPlay()" << endl;
    // mill.dailyTestPlay();
    // cout << endl;
  
    // cout << endl;

}

