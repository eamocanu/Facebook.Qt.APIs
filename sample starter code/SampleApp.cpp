#include <QtCore>
#include <QtGui>

#include "SampleApp.h"
#include "Facebook.h"


SampleApp::~SampleApp(){
	delete face;
	delete photoUploader;
}


//this class is a sample of how to use some of the Facebook APIs
SampleApp::SampleApp(){
	//I created a sample app to allow you to post to your wall and such.
	//Just run this module and it will ask you to give permissions to the
	//app to upload a file from your disk
	QString Application_ID="288229791195831";//TODO replace w your own app ID
	face= new Facebook (Application_ID);

	//to publish photo to Wall, the photo must already exist on some server
	//the code here uploads it to a server (your server) so then when FB APIs
	//are called to publish the photo, we already have the photo on a server
	//photoUploader= new PhotoUploader(ROOT_URL);

	connect(face, SIGNAL(logInFinished()), this, SLOT(publishPhoto()));
	connect(face, SIGNAL(photoUploadFinished()), this, SLOT(uploadFinished()));
	
	face->logIn();
}


/* Photo upload and publish to wall test method */
void SampleApp::publishPhoto(){
	//UNCOMMENT ONE(or both) OF THE OPERATIONS BELOW to experience posting to album or publishing to wall

	localPhotoPath="D:/file.jpg";//make sure you have this file on your disk

	//upload photos to album
	if (face->isLoginSuccessful()){
		face->uploadPhoto("SOME TITLE", localPhotoPath);
	}

	
	//publish photos to wall-not album
	if (face->isLoginSuccessful()){
		//QString remotePath="files/2/games/canvas";
		
		QString photoUrl="http://www.mentalfloss.com/wp-content/uploads/2007/05/435_rubiksCake.jpg";
		//QString photoUrl= photoUploader->getFullUrl(remotePath, localPhotoPath);
		//photoUploader->uploadPhoto(localPhotoPath, remotePath);
		
		PhotoData pData(photoUrl);
		face->publishPhoto(&pData);
	}
	
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


