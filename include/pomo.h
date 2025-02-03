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
        bool is_on();
        int get_num_epoch();
        int get_split();
};

#endif