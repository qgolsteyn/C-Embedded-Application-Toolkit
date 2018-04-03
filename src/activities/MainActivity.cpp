#include "MainActivity.h"

#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;

#include "Log.h"

RectangleView* bannerView;
ButtonView* playButtonView;
ButtonView* settingButtonView;
ScrollBarView* scrollBarView;
TextView* volumeText;

MainActivity::MainActivity() {
		bannerView = new RectangleView();
		playButtonView = new ButtonView();
		settingButtonView = new ButtonView();
		scrollBarView = new ScrollBarView();
		volumeText = new TextView();
}

MainActivity::~MainActivity() {
		delete bannerView;
		delete playButtonView;
		delete settingButtonView;
		delete scrollBarView;
		delete volumeText;
}

void MainActivity::onCreate() {
	Log_Low("MainActivity", "OnCreate()");

	Activity::attachView(bannerView);
	bannerView->attachView(playButtonView);
	bannerView->attachView(settingButtonView);
	bannerView->attachView(volumeText);
	bannerView->attachView(scrollBarView);

	bannerView->setX(0);
	bannerView->setY(400);
	bannerView->setWidth(800);
	bannerView->setHeight(80);
	bannerView->setColour(COLOR_WHITE);

	playButtonView->setX(10);
	playButtonView->setY(10);
	playButtonView->setWidth(60);
	playButtonView->setHeight(60);
	playButtonView->setColour(COLOR_BUTTON_DEFAULT);

	settingButtonView->setX(80);
	settingButtonView->setY(10);
	settingButtonView->setWidth(60);
	settingButtonView->setHeight(60);
	settingButtonView->addOnClickListener([](View* view) -> int {
		Log_Low("ButtonView", "Button clicked!");
		return 1;
	});

	volumeText->setX(360);
	volumeText->setY(10);
	volumeText->setWidth(200);
	volumeText->setHeight(60);
	volumeText->setTextColour(COLOR_GREY);
	volumeText->setText("0");
	volumeText->setHorizontalPos(H_LEFT);
	volumeText->setVerticalPos(V_CENTER);

	scrollBarView->setX(150);
	scrollBarView->setY(10);
	scrollBarView->setWidth(200);
	scrollBarView->setHeight(60);
	scrollBarView->addOnProgressListener([](View* view, int progress) -> void {
		ostringstream ostr;
		ostr << progress;
		volumeText->setText(ostr.str());
	});

	piSerial = new UartSerial("/dev/pi_uart");
	piSerial->writeLine("{\"isPlaying\":true,\"currentPlaying\":\"5aab770ab359b46a78887497\",\"currentStation\":{\"id\":\"5aab770ab359b46a78887497\",\"name\":\"CelePods5\",\"country\":{\"code\":\"CA\",\"name\":\"Canada\",\"latitude\":45.3168,\"longitude\":-73.8659},\"streamUrl\":\"http://144.217.192.113:8120/mount\",\"genre\":\"News\",\"createdAt\":1521186570,\"updatedAt\":1521186570},\"currentStreamUrl\":\"http://144.217.192.113:8120/mount\",\"currentSong\":{\"name\":\"A\",\"title\":\"HA\",\"imageUrl\":\"\"}}");
}

void MainActivity::onDestroy() {

}

string MainActivity::getName() {
  return "MainActivity";
}
