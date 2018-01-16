#include "ofApp.h"

//--------------------------------------------------------------
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
        serial.setDataType(OFXBSERIAL_DATA_TYPE_SINE_1HZ);
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
    if( serial.available() > 0 ){
        value.push_back(serial.read());
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
            serial.setDataType(OFXBSERIAL_DATA_TYPE_RANDOM);
            break;
            case '2':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_NOISE);
            break;
            case '3':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_SINE_1HZ);
            break;
            case '4':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_SINE_10HZ);
            break;
            case '5':
            serial.setDataType(OFXBSERIAL_DATA_TYPE_SINE_100HZ);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
