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

void ofxbSerial::setDataType(int _data_type, int _size_of_data)
{
    data_type = _data_type;
    size_of_data = _size_of_data;
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

string ofxbSerial::getLine()
{
    string s;
    s.clear();
    if( flg_dummy ){
        if( available() > 0 ){
            int d = read();
            for( int i = 0; i < size_of_data; i++ ){
                if( i == size_of_data-1 ){
                    s = s + ofToString(d);
                }
                else{
                    s = s + ofToString(d) + ",";
                }
            }

        }
    }
    else if( flg_dummy == false ){
        if( serial.available() > 0 ){
            unsigned char c[256];
            int ret;
            ret = serial.readBytes(c, sizeof(c));
            if( ret != OF_SERIAL_NO_DATA ){
                buf.append((char*)c, ret);
            }
        }
        
        
        int count_return = 0;
        int count_data_add = 0;
        bool flg_got_data = false;
        for( int i = 0; i < buf.size(); i++ ){
            if( buf[i] == 10 ){
                i = buf.size();
                count_data_add++;
                flg_got_data = true;
            }
            else if( buf[i] == 13 ){
                count_data_add++;
            }
            else{
                s.push_back(buf[i]);
                count_data_add++;
            }
        }
        
        if( flg_got_data == false ){
            s.clear();
        }
        else{
            for( int i = 0; i < count_data_add; i++ ){
                buf.erase(buf.begin());
            }
        }
    }

    return s;
}

vector<string> ofxbSerial::getList()
{
    string _s = getLine();
    vector<string> result;
    result.clear();
    
    if( _s.length() == 0 ){
        return result;
    }

    string str = "";
    int pos = 0;
    for( int i = 0; i < _s.length(); i++ ){
        if( _s.at(i) == ',' ){
            result.push_back(str);
            str.clear();
        }
        else{
            str = str + _s.at(i);
        }
    }
    if( str.length() > 0 ){
        result.push_back(str);
    }
    
    return result;
}


int ofxbSerial::read()
{
    static double theta = 0.0;
    static double theta_1 = 0.0;
    static double theta_2 = 0.0;
    static float x = 0.0;
    if( flg_dummy == true ){
        switch( data_type )
        {
            case OFXBSERIAL_DATA_TYPE_RANDOM:
                return ofRandom(-100, 100);
                break;
            case OFXBSERIAL_DATA_TYPE_NOISE:
                x=x+0.1;
                return 200*(ofNoise(x)-0.5);
                break;
            case OFXBSERIAL_DATA_TYPE_SINE_1HZ:
                theta = theta + 1*(2*M_PI)/sampling_rate; // 1Hz
                return 100*sin(theta);
                break;
            case OFXBSERIAL_DATA_TYPE_SINE_10HZ:
                theta = theta + 10*(2*M_PI)/sampling_rate; // 10Hz
                return 100*sin(theta);
                break;
            case OFXBSERIAL_DATA_TYPE_SINE_100HZ:
                theta = theta + 100*(2*M_PI)/sampling_rate; // 100Hz
                return 100*sin(theta);
                break;
            case OFXBSERIAL_DATA_TYPE_HEART:
                x=x+0.001;
                theta = theta + (0.5+(ofNoise(x))/2.0)*(2*M_PI)/sampling_rate;
//                theta_1 = theta_1 + (0.8+ofNoise(x)/2)*(2*M_PI)/sampling_rate;
                theta_2 = theta_2 + (1.5+ofNoise(x))*(2.0*M_PI)/sampling_rate;

                return 200*sin(theta)+100*sin(theta_1)+100*sin(theta_2);
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
