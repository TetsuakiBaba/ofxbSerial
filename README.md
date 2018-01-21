ofxbSerial
====

## Description
ofxbSerial is an ofSerial Wrapper to use serial port easily and simulate serial port without physical device.

1. If you set devide path as "dummy", you can get data from simulated serial port without physical devices, such as Arduino and so on.
2. You can omitt full path for serial port. ( ex. /dev/cu.usbmodem1441 --> /dev/cu.usb )
3. Same as Arduino Serial Plotter, send your device data csv(comma separated value) format. ofxbSerial::getList() will get each data on vector<string>. 

## Usage
```c++
void ofApp::setup(){
    ofSetVerticalSync(false);
    serial.setup("dummy", 9600);
    {
        /*
         Only when you set serial as "dummy", below settings work.
         Whenever you are in flight, train or outside of your office,
         you can simulate serial port for testing something.
         */
        serial.setSamplingRate(200); // 200 Hz per sec

        /*
         Format of data stream is supposed to be a csv(Comma Separeted
         Value) format, such as followings.
         10, 1491
         11, 1089
         12, 1950
         13, 8941
         ..
         ..
         ..
         */
        serial.setDataType(OFXBSERIAL_DATA_TYPE_SINE_1HZ, // Data Type
                           2); // How many number separated by a comma.
    }

    /*
     When you plug in some kind of serial port device, such as arduino,
     Only you can change is, port name. Furthermore, setup method will
     set automatically proper serial device by device path keyword.
     ofxbSerial::setup(string keyword_for_device_path, baudrate)

     If your Mac has /dev/cu.usbmodem1441 serial port, you can open your
     serial port below unless there is not any other same port name, such as
     /dev/cu.usbmodem1641 and so on.
     */
    // serial.setup("/dev/cu.usbmodem", 9600); // open Arduino Uno Device

}

//--------------------------------------------------------------
void ofApp::update(){
    vector<string>result = serial.getList();
    if( result.size() > 0 ){
        value.push_back( ofToInt(result[0]) );
        cout << result[0] << ", " << result[1] << endl;

        while( value.size() > ofGetWidth()/2 ){
            value.erase(value.begin());
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50,50,50);
    ofDrawBitmapString("ofxbSerial Example", 20, 20);
    ofDrawBitmapString("'1': RANDOM     ", 40, 40);
    ofDrawBitmapString("'2': NOISE      ", 40, 60);
    ofDrawBitmapString("'3': SINE 1HZ   ", 40, 80);
    ofDrawBitmapString("'4': SINE 10HZ  ", 40, 100);
    ofDrawBitmapString("'5': SINE 100HZ ", 40, 120);
    ofNoFill();
    ofSetPolyMode(OF_POLY_WINDING_ODD);
    ofBeginShape();
    for( int i = 0; i < value.size() ; i++ ){
        ofVertex(i+ofGetWidth()/4,
                 ofGetHeight()/2+value.at(i));
    }
    ofEndShape();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch( key ){
            case '1':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_RANDOM,2);
            break;
            case '2':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_NOISE,2);
            break;
            case '3':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_SINE_1HZ,2);
            break;
            case '4':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_SINE_10HZ,2);
            break;
            case '5':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_SINE_100HZ,2);
            break;
    }
}

```
See Example for more detailed.

## Licence
[MIT](https://opensource.org/licenses/MIT)

## Author
[TetsuakiBaba](https://github.com/TetsuakiBaba)
