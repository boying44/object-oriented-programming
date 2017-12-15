
#include <iostream>
#include <vector>
using namespace std;

class Instrument{
public:
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
};

void Instrument::makeSound() const{
    cout << "To make a sound..." << endl;
}

class Brass: public Instrument{
public:
    Brass(int mouthpiece): mouthpiece(mouthpiece){}
    void makeSound() const{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }
private:
    int mouthpiece;
};

class String: public Instrument{
public:
    String(int pitch): pitch(pitch){}
    void makeSound() const{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    int pitch;
};

class Percussion: public Instrument{
public:
    void makeSound() const{
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
private:
};

class Trombone: public Brass{
public:
    Trombone(int mouthpiece): Brass(mouthpiece){}
    void play() const{
        cout << "Blat ";
    }
};
class Trumpet: public Brass{
public:
    Trumpet(int mouthpiece): Brass(mouthpiece){}
    void play() const{
        cout << "Toot ";
    }
};

class Cello: public String{
public:
    Cello(int pitch): String(pitch){}
    void play() const{
        cout << "Squawk ";
    }
};
class Violin: public String{
public:
    Violin(int pitch): String(pitch){}
    void play() const{
        cout << "Screech ";
    }
};

class Drum: public Percussion{
    void play() const{
        cout << "Boom ";
    }
};
class Cymbal: public Percussion{
    void play() const{
        cout << "Crash ";
    }
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
    void play() const {
        if(instr)
            instr->play();
    }
private:
    Instrument* instr;
};

class MILL{
public:
    void receiveInstr(Instrument& instrument){
        for (int i = 0; i < instruments.size(); ++i){
            if(!instruments[i]){
                instruments[i] = &instrument;
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
    }
    Instrument* loanOut() {
        for (int i = 0; i < instruments.size(); ++i){
            if(instruments[i]){
                Instrument* ret(instruments[i]);
                instruments[i] = nullptr;
                return ret;
            }
        }
        return nullptr;
    }
private:
    vector<Instrument*> instruments;
};

class Orch{
public:
    void addPlayer(Musician& musician){
        musicians.push_back(&musician);
    }
    void play() const{
        for(Musician* m: musicians){
            m->play();
        }
        cout << endl;
    }
private:
    vector<Musician*> musicians;
};

// PART TWO
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    
    
    // THE SCENARIO
    
    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);
    
    //The orchestra performs
    cout << "orch performs\n";
    orch.play();
    
    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(*mill.loanOut());
    orch.addPlayer(sue);
    
    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(*mill.loanOut());
    
    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(*mill.loanOut());
    orch.addPlayer(mary);
    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    // Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(*mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(*mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(*mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(*mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main

