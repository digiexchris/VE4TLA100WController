#ifndef STATE_H
#define STATE_H

class State {
    protected:
        enum state { tx, rx, error };
        
    public: 
        enum Band { b160m, b80m, b60m, b40m, b30m, b20m, b17m, b15m, b12m, b10m, b6m };
        State(); 
};

#endif