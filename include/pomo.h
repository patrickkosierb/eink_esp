#ifndef POMO_H
#define POMO_H

class pomo{
    private:
        int num_epoch;
        int split; 
        int state; 

    public:
        pomo(int ne, int s);
        ~pomo();
        void start();
        void stop();
        void reset();
        bool get_state();
};

#endif