#ifndef PARAMETERS_H
#define PARAMETERS_H

class parameters
    {
        public:
        union param1
        {
            int param1val;
            int* param1addr;
        };

        union param2      {
            int param2val;
            int* param2addr;
        };

        union param3      {
            int param3val;
            int* param3addr;
        };

        bool isp1addr;
        bool isp2addr;
        bool isp3addr;

        param1 p1;
        param2 p2;
        param3 p3;

        parameters():isp1addr(false),isp2addr(false),isp3addr(false){}
};

#endif
