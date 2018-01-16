#include "ofxbSerial.h"


void ofxbSerial::setup(string keyword_device_name, int baudrate)
{
    // For dummy serial port
    if( keyword_device_name == "dummy"){
        flg_dummy = true;
        portname = "dummy port";
        sampling_rate = 30; // 30 times / second
    }
    else{
        flg_dummy = false;
        int find = 0;
        for( int i = 0;i < serial.getDeviceList().size(); i++ ){
            string candidate = serial.getDeviceList()[i].getDevicePath();
            
            if( candidate.substr(0, strlen(keyword_device_name.c_str())) == keyword_device_name) {
                if( serial.setup(candidate.c_str(), baudrate) ){
                    portname = candidate;
                    return;
                }
                ofSystemAlertDialog("Serial Init failed");
                ofExit();
            }
            else{
                cout << serial.getDeviceList()[i].getDevicePath() << endl;
            }
        }
        
        ofSystemAlertDialog("There is no proper serial device to be connected. Check your device port name.");
        ofExit();
    }
}

void ofxbSerial::setDataType(int _data_type)
{
    data_type = _data_type;
}

void ofxbSerial::setSamplingRate(int _sampling_rate)
{
    sampling_rate = _sampling_rate;
}
void ofxbSerial::write(string _s)
{
    if( flg_dummy == false ){
        serial.writeBytes((unsigned char*)_s.c_str(), _s.length());
    }
    else{
        cout << "ofxbSerial::write(): send " << _s << endl;
    }
}

int ofxbSerial::available(){
    if( flg_dummy == true ){
        if( (ofGetElapsedTimeMillis()-timestamp) >= 1000.0/(float)sampling_rate ){
            timestamp = ofGetElapsedTimeMillis();
            return 1;
        }
        else{
            return -1;
        }
    }
    else{
        return serial.available();
    }
}


int ofxbSerial::read()
{
    static double theta = 0.0;
    if( flg_dummy == true ){
        switch( data_type )
        {
            case OFXBSERIAL_DATA_TYPE_RANDOM:
                return ofRandom(-100, 100);
                break;
            case OFXBSERIAL_DATA_TYPE_NOISE:
                static float x = 0.0;
                x=x+0.1;
                return 200*(ofNoise(x)-0.5);
                break;
            case OFXBSERIAL_DATA_TYPE_SINE_1HZ:
                theta = theta + 1*(2*3.14)/sampling_rate; // 1Hz
                return 100*sin(theta);
                break;
            case OFXBSERIAL_DATA_TYPE_SINE_10HZ:
                theta = theta + 10*(2*3.14)/sampling_rate; // 10Hz
                return 100*sin(theta);
                break;
            case OFXBSERIAL_DATA_TYPE_SINE_100HZ:
                theta = theta + 100*(2*3.14)/sampling_rate; // 100Hz
                return 100*sin(theta);
                break;
                
        }
        



    }
    else{
        return serial.readByte();
    }
}

int ofxbSerial::write(unsigned char _c)
{
    serial.writeByte(_c);
}
