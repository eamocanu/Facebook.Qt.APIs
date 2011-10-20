#include <QtCore>
#include <QtGui>

#include "SampleApp.h"
#include "Facebook.h"



SampleApp::~SampleApp(){
	delete face;
	delete photoUploader;
	delete window;
	//delete fbui2;
	//delete fbui3;
}

//this class is a sample of how to use the facebook APIs
SampleApp::SampleApp(){
	connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkReply(QNetworkReply*)));

	QString ELC_Application_ID="112189648850879";
	face= new Facebook (ELC_Application_ID);
	photoUploader= new PhotoUploader(ROOT_URL);

	connect(face, SIGNAL(logInFinished()), this, SLOT(publishPhoto()));
	connect(face, SIGNAL(photoUploadFinished()), this, SLOT(uploadFinished()));
	
	//face->logIn();

	doStuff();
}

void SampleApp::doStuff(){
	window= new UIFBmain();
	fbui2 = new UIFBUser();
	fbui3 = new UIFBUser();

	
	fbui2->setUserName("pretend name 1");
	fbui2->setUserLocation("location 1");
	//fbui2->resize(200,200);

	
	fbui3->setUserName("pretend name 2");
	fbui3->setUserLocation("waterloo");
	//fbui3->resize(100,100);

	window->addUser(fbui2);
	window->addUser(fbui3);

	window->resize(400,400);
	window->show();
}

void SampleApp::publishPhoto(){
	qDebug()<<"log in finished";

	//TODO replace with your own LOCAL PATH OR pass the one from games 
	localPhotoPath="D:/file.jpg";

	//upload photos to album
	if (face->isLoginSuccessful()){
		face->uploadPhoto("you are my butterfly", localPhotoPath);
	}

	FBUser* user= face->getCurrentlyActiveUser();

	window= new UIFBmain();
	fbui2 = new UIFBUser();
	fbui3 = new UIFBUser();

	//add the same user twice to the UI
	fbui2->setUserPhoto(user->mainPhoto);
	fbui2->setUserName(user->name);
	fbui2->setUserLocation(user->location);

	fbui3->setUserPhoto(user->mainPhoto);
	fbui3->setUserName(user->name);
	fbui3->setUserLocation(user->location);

	window->addUser(fbui2);
	window->addUser(fbui3);

	window->resize(400,400);
	window->show();	
}


void SampleApp::uploadFinished(){
	if (!face->isPhotoUploadSuccessful()){
		//try again?
		;
		qDebug()<<"upload failed" ;
	} else {
		qDebug()<<"upload successful" ;
	}
}


void SampleApp::parseNetworkReply(QNetworkReply* reply){
	QByteArray response(reply->readAll());
	fbui.setUserPhoto(&response);
}
