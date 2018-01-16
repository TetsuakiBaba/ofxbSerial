#pragma once

#include "ofMain.h"

#define OFXBSERIAL_DATA_TYPE_RANDOM 1
#define OFXBSERIAL_DATA_TYPE_SINE_1HZ 2
#define OFXBSERIAL_DATA_TYPE_SINE_10HZ 3
#define OFXBSERIAL_DATA_TYPE_SINE_100HZ 4
#define OFXBSERIAL_DATA_TYPE_NOISE 10


class ofxbSerial{
public:
    void setup(string keyword_device_name, int baudrate);
    ofSerial serial;
    string portname;
    bool flg_dummy;
    
    int available();
    int read();
    int write(unsigned char _c);
    void write(string _s);
    void setSamplingRate(int _sampling_rate);
    void setDataType(int _data_type);
    int sampling_rate;
    int data_type;
    
    unsigned long int timestamp;
};

