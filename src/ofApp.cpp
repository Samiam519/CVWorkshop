#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = 640;
    camHeight = 480;
    
    cam.setup(camWidth, camHeight);
    colorImg.allocate(640,480);
    grayImage.allocate(640,480);
    grayBg.allocate(640,480);
    grayDiff.allocate(640,480);
    
    threshold = 80;
    //ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    bool bNewFrame = false;
    
    cam.update();
    bNewFrame = cam.isFrameNew();
    if (bNewFrame){
        
        colorImg.setFromPixels(cam.getPixels());
        
        grayImage = colorImg;
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to false so we won't get interior contours
        contourFinder.findContours(grayDiff, 20, (340*480)/3, 10, false);	// find holes
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
        particles[i].addForce(0,0.4);  // gravity
        particles[i].addDampingForce();
        particles[i].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i = 0; i < contourFinder.nBlobs; i++) {
        ofSetColor(ofRandom(0, 255),
                   ofRandom(0, 255),
                   ofRandom(0, 255));
        ofDrawCircle(contourFinder.blobs[i].boundingRect.x, contourFinder.blobs[i].boundingRect.y, 5);
        //ofDrawRectangle(contourFinder.blobs[i].centroid, contourFinder.blobs[i].boundingRect.width, contourFinder.blobs[i].boundingRect.height);
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
    
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
    for(int i = 0; i < contourFinder.nBlobs; i++) {
        if(abs(contourFinder.blobs[i].boundingRect.x - x) < 10 && abs(contourFinder.blobs[i].boundingRect.y - y) < 10){
            //mouse press blob
            cout << "collison" << endl;
            ofSetColor(255,0,0);
//            for (int i = 0; i < particles.size(); i++){
//                float vx = ofRandom(-4,4);
//                float vy = ofRandom(-4,4);
//                particles[i].setInitialCondition(mouseX,mouseY,vx, vy);
//                
//            }
            for (int i = 0; i < 500; i++){
                Particle myParticle;
                float vx = ofRandom(-10,10);
                float vy = ofRandom(-10,10);
                myParticle.setInitialCondition(x,y,vx, vy);
                // more interesting with diversity :)
                // uncomment this:
                myParticle.damping = ofRandom(0.01, 0.05);
                particles.push_back(myParticle);
            }
        }
    }
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
