#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

	// load in sounds:
	/*beat.loadSound("sounds/jdee_beat.mp3");
	ow.loadSound("sounds/ow.mp3");
	dog.loadSound("sounds/dog.mp3");
	rooster.loadSound("sounds/rooster.mp3");*/
	beat4.loadSound("sounds/beat4.mp3");
    something.loadSound("sounds/something.mp3");
    beat5.loadSound("sounds/beat5.mp3");
    daftpunk.loadSound("sounds/daftpunkish.mp3");
    energybros.loadSound("sounds/energybros.mp3");
    tobacco.loadSound("sounds/dirt.mp3");
    seeds.loadSound("sounds/NewSeeds.mp3");
    mass.loadSound("sounds/Nightcall.mp3");

    song = "N/A";
    artist = "N/A";
    help = true;


	play = false;
	playingNow = 0;
	fftStyle = 1;

	// we will bounce a circle using these variables:
	px = 270;
	py = 160;
	vx = 0;
	vy = 0;


    bgRed =0;
    bgGreen = 0;
    bgBlue =0;
    red = 255;
    green = 255;
    blue = 255;
	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}

	nBandsToGet = 2048;
}


//--------------------------------------------------------------
void testApp::update(){


    //    ofBackgroundGradient(ofColor::purple, ofColor::black);

	// update the sound playing system:
	ofSoundUpdate();

	// (1) we increase px and py by adding vx and vy
	px += vx;
	py += vy;

	// (2) check for collision, and trigger sounds:
	// horizontal collisions:
	if (px < 0){
		px = 0;
		vx *= -1;
		//dog.play();
	} else if (px > ofGetWidth()){
		px = ofGetWidth();
		vx *= -1;
		//ow.play();
	}
	// vertical collisions:
	if (py < 0 ){
		py = 0;
		vy *= -1;
		//rooster.play();
	} else if (py > ofGetHeight()){
		py = ofGetHeight();
		vy *= -1;
		//beat4.play();
	}
	// (3) slow down velocity:
	vx 	*= 0.996f;
	vy 	*= 0.996f;

	// (4) we use velocity for volume of the samples:
	float vel = sqrt(vx*vx + vy*vy);
	ow.setVolume(MIN(vel/5.0f, 1));
	beat.setVolume(MIN(vel/5.0f, 1));
	dog.setVolume(MIN(vel/5.0f, 1));
	rooster.setVolume(MIN(vel/5.0f, 1));
	/*beat4.setVolume(MIN(vel/5.0f, 1));
	something.setVolume(MIN(vel/5.0f, 1));
	beat5.setVolume(MIN(vel/5.0f, 1));
	daftpunk.setVolume(MIN(vel/5.0f, 1));*/

	// (5) grab the fft, and put in into a "smoothed" array,
	//		by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){

		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.96f;

		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

	}


}

//--------------------------------------------------------------
void testApp::draw(){
    if(red<bgRed){
        red += 1;
    }
    if(red>bgRed){
        red -= 1;
    }
    if (green < bgGreen){
        green += 1;
    }
    if (green > bgGreen){
        green -= 1;
    }
    if(blue < bgBlue)
    {
        blue += 1;
    }
    if(blue > bgBlue)
    {
        blue -= 1;
    }
    ofBackground(red,green,blue);

    ofEnableAlphaBlending();
	// draw the fft resutls:
	if(playingNow == 7)
    {
        ofSetColor(red*25+5,green*10+5,blue*18);
    }
    else if (playingNow == 8)
    {
        ofSetColor(green+27,blue*2+55,red*0);
    }
    else
    {
        ofSetColor(blue,red,green);
    }
	float width = (float)(5*1024) / nBandsToGet;

	if(fftStyle == 2)
    {
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		ofRect(i*width,ofGetHeight(),width,-(fftSmoothed[i] * 800));
		ofRect(i*width,0,width,(fftSmoothed[i] * 800));
		ofRect(ofGetWidth()-i*width,0,width,(fftSmoothed[i] * 800));
		ofRect(ofGetWidth()-i*width,ofGetHeight(),width,-(fftSmoothed[i] * 800));
	}
        red = red + (float)fftSmoothed[8]/2;
        green = green + (float)fftSmoothed[8]/2;
        blue = blue + (float)fftSmoothed[8]/2;
    }

    if(fftStyle == 1)
    {
        for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		ofRect((ofGetWidth()/2)+(i*width),ofGetHeight()/2,width,-(fftSmoothed[i] * 400));
		ofRect((ofGetWidth()/2)+(i*width),ofGetHeight()/2,width,(fftSmoothed[i] * 400));
		ofRect((ofGetWidth()/2-i*width),ofGetHeight()/2,width,(fftSmoothed[i] * 400));
		ofRect((ofGetWidth()/2-i*width),ofGetHeight()/2,width,-(fftSmoothed[i] * 400));
	}
        red = red + (float)fftSmoothed[8]/2;
        green = green + (float)fftSmoothed[8]/2;
        blue = blue + (float)fftSmoothed[8]/2;
    }

    if(fftStyle == 3)
    {
        for (int i = 0;i < nBandsToGet; i++){
        ofRect(i*width,ofGetHeight(),width,-(fftSmoothed[i] * 200));
		ofRect(i*width,ofGetHeight()/2,width,(fftSmoothed[i] * 200));
		ofRect(ofGetWidth()-i*width,ofGetHeight()/2,width,(fftSmoothed[i] * 200));
		ofRect(ofGetWidth()-i*width,ofGetHeight(),width,-(fftSmoothed[i] * 200));

		ofRect((ofGetWidth()/2)+(i*width),ofGetHeight(),width,-(fftSmoothed[i] * 400));
		ofRect((ofGetWidth()/2)+(i*width),ofGetHeight()/2,width,(fftSmoothed[i] * 400));
		ofRect((ofGetWidth()/2-i*width),ofGetHeight()/2,width,(fftSmoothed[i] * 400));
		ofRect((ofGetWidth()/2-i*width),ofGetHeight(),width,-(fftSmoothed[i] * 400));
        }
        red = red + (float)fftSmoothed[8]/2;
        green = green + (float)fftSmoothed[8]/2;
        blue = blue + (float)fftSmoothed[8]/2;
    }

    ofDisableAlphaBlending();
	// finally draw the playing circle:

	ofEnableAlphaBlending();

        if(playingNow == 7)
        {
            ofSetColor(red*25+5,green*10+5,blue*18,100);
        }

        else if (playingNow == 8)
        {
            ofSetColor(green+27,blue*2+55,red*0,100);
        }
        else
        {
            ofSetColor(green,blue,red,100);
        }

		float circleWidth = (float)(5*1024) / nBandsToGet;

		if (fftStyle == 2 || fftStyle == 1)
        {
            int j = 1;
            for (int i = 0;i < nBandsToGet; i++){
                if(j == 1){
                    ofCircle(ofGetWidth()/4, ofGetHeight()/4,-(fftSmoothed[i] * 100));
                    j++;
                }
                else if(j == 2)
                {
                    ofCircle((3*ofGetWidth())/4,ofGetHeight()/4,-(fftSmoothed[i] * 100));
                    j++;
                }
                else if(j == 3)
                {
                    ofCircle(ofGetWidth()/4, (3*ofGetHeight())/4,-(fftSmoothed[i] * 100));
                    j++;
                }
                else if(j == 4)
                {
                    ofCircle((3*ofGetWidth())/4, (3*ofGetHeight())/4,-(fftSmoothed[i] * 100));
                    j=1;
                }
            }
        }

        if(fftStyle == 3)
        {
            int j = 1;
            for (int i = 0;i < nBandsToGet; i++){

                if (j == 1)
                {
                    ofCircle(ofRandom((ofGetWidth()/4)-10,(ofGetWidth()/4)+10), ofRandom((ofGetHeight()/4)-10, (ofGetHeight()/4)+10),-(fftSmoothed[i] * 75));
                    j++;
                }

                if (j == 2)
                {
                    ofCircle(ofRandom(((3*ofGetWidth())/4)-10,((3*ofGetWidth())/4)+10),ofRandom((ofGetHeight()/4)-10,(ofGetHeight()/4)+10),-(fftSmoothed[i] * 75));
                    j=1;
                }

            }
        }
		//ofCircle(px, py,50);
	ofDisableAlphaBlending();

	ofSetHexColor(0xffffff);
	ofDrawBitmapString("Fps: "+ ofToString(ofGetFrameRate()), 15,15);
	ofDrawBitmapString("Song: "+ ofToString(song),15,30);
	ofDrawBitmapString("Artist: "+ofToString(artist),15,45);
	ofDrawBitmapString("Press H for help",15,75);

    if(help == true)
    {
        ofDrawBitmapString("Quit Visualizer: ESC",15,90);
        ofDrawBitmapString("Change Song: A or D",15,105);
        ofDrawBitmapString("Change Visualization: 1, 2, or 3",15,120);
        ofDrawBitmapString("1: Rorschach",15,135);
        ofDrawBitmapString("2: Sludge Pit",15,150);
        ofDrawBitmapString("3: Closet Monster",15,165);
    }
	//ofCircle(px, py,8);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

    if(key == '1')
    {
        fftStyle = 1;
    }
    if (key == '2')
    {
        fftStyle = 2;
    }

     if (key == '3')
    {
        fftStyle = 3;
    }

    if(key == 'h'||key == 'H')
    {
        if(help == true)
        {
            help = false;
        }
        else
        {
            help = true;
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == OF_KEY_RIGHT || key == '6'|| key == 'd' || key =='D')
    {


        if(playingNow == 0)
        {
            beat4.play();
            playingNow = 1;
            play = true;
            bgRed = 147;
            bgGreen = 112;
            bgBlue = 219;
            song = "Ghost Party";
            artist = "C-Reg";

        }

        else if(playingNow == 1)
        {
            beat4.stop();
            something.play();
            playingNow = 2;
            play = true;
            bgRed = 85;
            bgGreen = 107;
            bgBlue = 47;
            song = "Something";
            artist = "C-Reg";
        }

        else if(playingNow == 2)
        {
            something.stop();
            beat5.play();
            playingNow = 3;
            play = true;
            bgRed = 106;
            bgGreen = 90;
            bgBlue = 205;
            song = "A Taste of a Beat";
            artist = "C-Reg ft. Herb Alpert";
        }

        else if(playingNow == 3)
        {
            beat5.stop();
            daftpunk.play();
            playingNow = 4;
            play = true;
            bgRed = 184;
            bgGreen = 134;
            bgBlue = 11;

            song = "Spies on the Street";
            artist = "C-Reg";
        }
        else if(playingNow == 4)
        {
            daftpunk.stop();
            energybros.play();
            playingNow = 5;
            play = true;
            bgRed = 255;
            bgGreen = 108;
            bgBlue = 180;
            song = "Energy Bros. Back in Action";
            artist = "C-Reg ft. Bear Patrol";
        }
        else if(playingNow == 5)
        {
            energybros.stop();
            tobacco.play();
            playingNow = 6;
            play = true;
            bgRed = 32;
            bgGreen = 178;
            bgBlue = 170;
            song = "Dirt";
            artist = "Tobacco ft. Aesop Rock";
        }
        else if(playingNow == 6)
        {
            tobacco.stop();
            mass.play();
            playingNow = 7;
            play = true;
            bgRed = 10;
            bgGreen = 10;
            bgBlue = 10;
            song = "Nightcall";
            artist = "Kavinsky ft. Lovefoxxx";
        }
        else if(playingNow == 7)
        {
            mass.stop();
            seeds.play();
            playingNow = 8;
            play = true;
            bgRed = 100;
            bgGreen = 100;
            bgBlue = 100;
            song = "New Seeds";
            artist = "Boards of Canada";
        }

        else if(playingNow == 8)
        {
            seeds.stop();
            beat4.play();
            playingNow = 1;
            play = true;
            bgRed = 147;
            bgGreen = 112;
            bgBlue = 219;
            song = "Ghost Party";
            artist = "C-Reg";
        }
    }
    if (key ==OF_KEY_LEFT || key == '4' || key == 'a'||key =='A')
    {
        if(playingNow == 0)
        {
            seeds.play();
            playingNow = 8;
            play = true;
            bgRed = 100;
            bgGreen = 100;
            bgBlue = 100;
            song = "New Seeds";
            artist = "Boards of Canada";

        }
        else if(playingNow == 8)
        {
            seeds.stop();
            mass.play();
            playingNow = 7;
            play = true;
            bgRed = 10;
            bgGreen = 10;
            bgBlue = 10;
            song = "Nightcall";
            artist = "Kavinsky ft. Lovefoxxx";

        }
        else if(playingNow == 7)
        {
            mass.stop();
            tobacco.play();
            playingNow = 6;
            play = true;
            bgRed = 32;
            bgGreen = 178;
            bgBlue = 170;
            song = "Dirt";
            artist = "Tobacco ft. Aesop Rock";
        }
        else if(playingNow == 6)
        {
            tobacco.stop();
            energybros.play();
            playingNow = 5;
            play = true;
            bgRed = 255;
            bgGreen = 105;
            bgBlue = 180;
            song = "Energy Bros. Back in Action";
            artist = "C-Reg ft. Bear Patrol";

        }

        else if(playingNow == 5)
        {
            energybros.stop();
            daftpunk.play();
            playingNow = 4;
            play = true;
            bgRed = 184;
            bgGreen = 134;
            bgBlue = 11;
            song = "Spies on the Street";
            artist = "C-Reg";
        }

        else if(playingNow == 4)
        {
            daftpunk.stop();
            beat5.play();
            playingNow = 3;
            play = true;
            bgRed = 106;
            bgGreen = 90;
            bgBlue = 205;
            song = "A Taste of a Beat";
            artist = "C-Reg ft. Herb Alpert";
        }

        else if(playingNow == 3)
        {
            beat5.stop();
            something.play();
            playingNow = 2;
            play = true;
            bgRed = 85;
            bgGreen = 107;
            bgBlue = 47;
            song = "Something";
            artist = "C-Reg";
        }

        else if(playingNow == 2)
        {
            something.stop();
            beat4.play();
            playingNow = 1;
            play = true;
            bgRed = 147;
            bgGreen = 112;
            bgBlue = 219;
            song = "Ghost Party";
            artist = "C-Reg";
        }
        else if(playingNow == 1)
        {
            beat4.stop();
            seeds.play();
            playingNow = 8;
            play = true;
            bgRed = 100;
            bgGreen = 100;
            bgBlue = 100;
            song = "New Seeds";
            artist = "Boards of Canada";
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	// add into vx and vy a small amount of the change in mouse:
/*	vx += (x - prevx) / 20.0f;
	vy += (y - prevy) / 20.0f;
	// store the previous mouse position:
	prevx = x;
	prevy = y;*/
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	//prevx = x;
	//prevy = y;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

