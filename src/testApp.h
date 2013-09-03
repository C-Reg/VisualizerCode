#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofSoundPlayer 		beat;
		ofSoundPlayer		ow;
		ofSoundPlayer		dog;
		ofSoundPlayer		rooster;
		ofSoundPlayer       beat4;
		ofSoundPlayer       something;
		ofSoundPlayer       beat5;
		ofSoundPlayer       daftpunk;
		ofSoundPlayer       energybros;
		ofSoundPlayer       tobacco;
		ofSoundPlayer       mass;
		ofSoundPlayer       seeds;

		float 				* fftSmoothed;
		// we will draw a rectangle, bouncing off the wall:
		float 				px, py, vx, vy;

		int nBandsToGet;
		float prevx, prevy;
		bool play;
		int playingNow;
		string song;
		string artist;
		bool help;


		float bgRed;
		float bgGreen;
		float bgBlue;
		float red;
		float green;
		float blue;

		int fftStyle;
};

