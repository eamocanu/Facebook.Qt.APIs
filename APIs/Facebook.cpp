/**
 * Experimental Facebook APIs
 *
 * Created by Adrian M in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs/downloads
 * Git repository https://github.com/eamocanu/Facebook.Qt.APIs
 */

/* Released under the BSD license
	Copyright 2010 Adrian M. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Adrian M ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Adrian M.
*/

#include "Facebook.h"

/*  clientID: facebook application ID on whose behalf to act
	redirectURI: facebook needs to redirect user to some page after login
				 by default it uses REDIRECT_URI because the browser window is 
				 hidden so it doesn't matter right now
	display: touchscreen or popup. Since touch is buggy it defaults to popup */
Facebook::Facebook(QString clientID, QString redirectURI, QString display):clientID(clientID),redirectURI(redirectURI),display(display){
	photoUploadStatus= FBNetworkRequest::FAIL;
	logInStatus= FBNetworkRequest::FAIL;
	crtUserProfileUrl="";
	authToken="";

	loginUrl= URL;
	loginUrl= loginUrl.arg(this->clientID).arg(this->redirectURI).arg(this->display);
	
	connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkReply(QNetworkReply*)));
	
	webView= new QWebView();
	frame= webView->page()->mainFrame();
	webView->show();

	connect(webView, SIGNAL(urlChanged(const QUrl &) ), this, SLOT(urlChanged(const QUrl &)) );
	connect(&requestTimer, SIGNAL(timeout()), this, SLOT(onReplyTimeout()));
	connect(this, SIGNAL(getTextUserDataFinished()), this, SLOT(getMainPhotoUrl()));
	connect(this, SIGNAL(mainPhotoUrlLoaded()), this, SLOT(loadMainPhoto()));
}


Facebook::~Facebook(void){
	delete webView;
}


/* Logs into FB and retrieves user data (email, photo Url, etc). Emits logInFinished() when done */
void Facebook::logIn(){
	webView->load(loginUrl);
}


/* Upload photo to APPLICATION_NAME album. ie: uses name of whatever your facebook app is called
	title: photo caption
	filePath: location of file */
void Facebook::uploadPhoto(const QString &title, const QString &filePath){
	QFile f(filePath, this);
	if(!f.open(QIODevice::ReadOnly)){
		qDebug()<<"error opening file "<<filePath;
		return;
	}
	
	uploadPhoto(title, &f.readAll());
	f.close();
}


/* Upload photo to APPLICATION_NAME album. ie: uses name of whatever your facebook app is called
	title: photo caption
	photoData: photo file bytes */
void Facebook::uploadPhoto(const QString &title, const QByteArray *photoData){
	checkUsersLoggedIn();

	FBNetworkRequest* fbRequest= new FBNetworkRequest(WALL_PHOTOS_PATH, &photoUploadStatus, FBNetworkRequest::POST);
	fbRequest->addPhotoPostData(authToken, photoData, title);
	fbRequest->setType(FBNetworkRequest::PHOTO_UPLOAD);

	addRequestToQueue(fbRequest);
}


/* Publishes photo to user's wall based on PhotoData object. 
	Photo must already be uploaded on a server */
void Facebook::publishPhoto(const PhotoData *photoData){
	checkUsersLoggedIn();

	QByteArray data;
	FBNetworkRequest* fbRequest;

	//ADD PARAMETERS
	data.append("name="+photoData->postLinkTitle);
	data.append("&caption="+photoData->postTitle);
	data.append("&description="+photoData->postText);
	data.append("&link="+photoData->postLinkUrl);
	data.append("&picture="+photoData->postPhotoUrl);

	//add privacy and authorization
	data.append("&privacy={\"value\": \"ALL_FRIENDS\"}");
	data.append("&access_token=" + authToken);
	
	fbRequest= new FBNetworkRequest(WALL_PUBLISH_PATH, &photoPublishStatus, FBNetworkRequest::POST);
	fbRequest->setType(FBNetworkRequest::PHOTO_PUBLISH);
	fbRequest->addTextPostData(&data);

	addRequestToQueue(fbRequest);
}


/* Issue request for retrieving data of user currently logged in. 
	When done emits loadUserDataFinished()
	Called automatically during log in */
void Facebook::getCurrentUserData(){
	FBNetworkRequest* fbRequest;
	QString url(USER_DATA);
	url.append("&access_token=" + authToken);
	
	fbRequest= new FBNetworkRequest(url, &userInfoRetrievedStatus, FBNetworkRequest::GET);
	fbRequest->setExpectingJSONReply(true);
	fbRequest->setType(FBNetworkRequest::GET_USER_DATA_REQUEST);
	addRequestToQueue(fbRequest);
}


/* Called after login token and user text data is received. 
		Retrieves and stores user main photo with user data */
void Facebook::getMainPhotoUrl(){
	QString url(BASE_URL);
	url.append("/");
	url.append(USER_MAIN_PHOTO);
	url.append("&access_token=" + authToken);
	webView->load(url);
}


/* Called after the main photo URL has been forwarded to the correct on by facebook */
void Facebook::loadMainPhoto(){
	FBNetworkRequest* fbRequest= new FBNetworkRequest("", &mainPhotoRetrievedStatus, FBNetworkRequest::GET);
	fbRequest->setType(FBNetworkRequest::GET_MAIN_PHOTO);
	
	FBUser *user= userManager.getUser(crtUserProfileUrl);
	if (user == 0) return;

	//use custom URL (non FB) - photos are stored somewhere else
	fbRequest->setUrl(user->mainPhotoUrl);
	addRequestToQueue(fbRequest);
}


/* See how many users are logged in.
	If no user is logged in, it forwards to logIn()
	If more users are logged in, emits multipleUsersLoggedIn() */
void Facebook::checkUsersLoggedIn(){
	if (userManager.getNumUsers()==0){
		logIn();
	} else if (userManager.getNumUsers()>1){
		qDebug()<<"Multiple users logged in. Send as which?";
		//lets receiver set active user by getting input from user
		emit multipleUsersLoggedIn();
	}
}


/* Returns numbers of users currently logged into facebook */
int Facebook::getNumUsers(){
	return userManager.getNumUsers();
}


/* Set active user the user corresponding to mainPhotoUrl */
void Facebook::setCurrentlyActiveUser(QString mainPhotoUrl){
	authToken= userManager.getToken(mainPhotoUrl);
	crtUserProfileUrl= userManager.getPhotoURL(mainPhotoUrl);
}


/* Returns currently active user: Last user which logged in is the current user */
FBUser* Facebook::getCurrentlyActiveUser(){
	//must use photo Url as key because tokens expire and are renewed (ie change)
	return userManager.getUser(crtUserProfileUrl);
}


/* Returns all users who have logged in */
QList<FBUser*> Facebook::getActiveUsers(){
	return userManager.getUsers();
}


/* Add request to queue to be sent. Request will be sent when it reaches head of queue */
void Facebook::addRequestToQueue(FBNetworkRequest *request){
	requestListMutex.lock();
		requestQueue.push_back(request);
	
		if (requestQueue.size()==1){
	requestListMutex.unlock();
			//start timeout timer: 30sec
			requestTimer.start(REQUEST_TIMEOUT*1000);
			sendMessage(request);
		} else {
	requestListMutex.unlock();
		}
}


/* Sends a request via network manager */
void Facebook::sendMessage(FBNetworkRequest *request){
	if (request->isPost()){
		networkManager.post( *(request->getNetworkRequest()), *(request->getPostData()) );
	}else if (request->isGet()){
		networkManager.get( *(request->getNetworkRequest()) );
	}
}


/* Returns status of login operation */
bool Facebook::isLoginSuccessful(){
	return (logInStatus==FBNetworkRequest::SUCCESS);
}


/* Returns status of photo upload operation */
bool Facebook::isPhotoUploadSuccessful(){
	return (photoUploadStatus==FBNetworkRequest::SUCCESS);
}


/* Returns status of photo publishing operation */
bool Facebook::isPhotoPublishSuccessful(){
	return (photoPublishStatus==FBNetworkRequest::SUCCESS);
}



/* Called when browser loads a new URL.
	The URL may contain the authentication token sent from FB */
void Facebook::urlChanged(const QUrl &qurl){
	QString url =qurl.toString();

	//parse authentication token
	if (url.contains(ACCESS_TOKEN)){
		int startIndex= url.indexOf(ACCESS_TOKEN);
		
		//find where access token key ends and a new param begins
		int endIndex= url.indexOf("&");
		if (endIndex<0){
			endIndex= url.length();
		}
		
		//"auth_token=..." get rid of the prefix including the = sign
		startIndex= startIndex+QString(ACCESS_TOKEN).length() +1;
		authToken= url.mid(startIndex, (endIndex-startIndex) );

		logInStatus= FBNetworkRequest::SUCCESS;
		webView->hide();
		
		getCurrentUserData();//populates FBUser Fields
		//emit logInFinished();

	} else if (url.contains("http://profile.")){//could check for png jpg etc
		//get photo either from webpage or use new URL to send a nwkManager request
		FBUser *user= userManager.getUser(crtUserProfileUrl);
		if (user==0) return;

		user->mainPhotoUrl= url;
		emit mainPhotoUrlLoaded();
	}
	
}


/* Called when reply is sent back from facebook. Used with network manager 
	Request at head of queue is dequeued and based on it, the information
	received in the reply is interpreted.
	If request was lost from the queue, returns silently with debug error message */
void Facebook::parseNetworkReply(QNetworkReply* reply){
	//Stop timer thread;
	requestTimer.stop();
	Facebook::Signal signal;

	requestListMutex.lock();
		if (requestQueue.size()<1){
	requestListMutex.unlock();
			qDebug()<<"network request has been deleted from queue before reply was received";
			QByteArray response(reply->readAll());
			QString resultString(response);
			qDebug()<<resultString;
			return;
		}

		FBNetworkRequest *lastRequest= requestQueue.first();
		
		if (!reply->error()) {
			signal= parseReplyData(lastRequest, reply->readAll());
		}else {
			//show network reply error:
			QByteArray response(reply->readAll());
			QString resultString(response);
			qDebug()<<resultString;
			
			lastRequest->setStatus(FBNetworkRequest::FAIL);
		}

		requestQueue.remove(0);
		reply->deleteLater();
		delete lastRequest;

		FBNetworkRequest *nextRequest=0;
		if ( requestQueue.size() >0){
			nextRequest= requestQueue.first();//peek
		}
	requestListMutex.unlock();//allow producers to add items to queue

		if (signal !=0){
			emit (this->*signal)();
		}
		if (nextRequest != 0){
			sendMessage(nextRequest);
		}
}


/* Parses reply data and emits signals for each request type 
	lastRequest: reply data is parsed according to info stored in this request 
	Returns signals for the request sent */
Facebook::Signal Facebook::parseReplyData(FBNetworkRequest *lastRequest, QByteArray replyData){
	JSONEvaluator jsEvaluator;
	QString jsonObject(replyData);

	if (jsonObject.contains("error")){
		lastRequest->setStatus(FBNetworkRequest::FAIL);
		qDebug()<<jsEvaluator.getErrorMessage();
		
		//has access token expired?
		if (jsEvaluator.getErrorMessage() == TOKEN_EXPIRED_ERROR || jsEvaluator.getErrorMessage() == TOKEN_MISSING_ERROR){
			qDebug()<<"Session expired or never started. Logging in again";
			//remove old session
			userManager.removeUser(crtUserProfileUrl);
			
			//let caller deal with it
			//emit sessionNeeded();
			return &Facebook::sessionNeeded;
		}
	} else {
		lastRequest->setStatus(FBNetworkRequest::SUCCESS);
	}

	if (lastRequest->getType() == FBNetworkRequest::GET_USER_DATA_REQUEST){
		if (lastRequest->isExpectingJSONReply()){
			jsEvaluator.setJSON(jsonObject);

			FBUser *fbUser = new FBUser();
			fbUser->name= jsEvaluator.getField("name");
			fbUser->email= jsEvaluator.getField("email");
			fbUser->token= this->authToken;
			fbUser->location= jsEvaluator.getLocation();
			fbUser->profileUrl= jsEvaluator.getField("link");
			
			userManager.addUser(fbUser);

			//save photo url to use as key because tokens expire and are renewed
			crtUserProfileUrl= fbUser->profileUrl;
		}
		return &Facebook::getTextUserDataFinished;
	} else if (lastRequest->getType() == FBNetworkRequest::PHOTO_UPLOAD){
		return &Facebook::photoUploadFinished;
	} else if (lastRequest->getType() == FBNetworkRequest::PHOTO_PUBLISH){
		return &Facebook::photoPublishFinished;
	} else if (lastRequest->getType() == FBNetworkRequest::GET_MAIN_PHOTO){
		FBUser *crtUser= userManager.getUser(crtUserProfileUrl);
		crtUser->mainPhoto= new QByteArray(replyData);
		return &Facebook::logInFinished;
	}
	
	
	return 0;
}


/* Called by timer when network reply times out. Emits networkReplyTimedOut() */
void Facebook::onReplyTimeout(){
	requestListMutex.lock();
		if (requestQueue.size()<1){
	requestListMutex.unlock();
			qDebug()<<"network request has been deleted from queue before reply was received";
			return;
		}
		
		FBNetworkRequest *lastRequest= requestQueue.first();
		lastRequest->setStatus(FBNetworkRequest::FAIL);
		requestQueue.remove(0);
	requestListMutex.unlock();
	
	lastRequest->setStatus(FBNetworkRequest::FAIL);
	//parseReplyData(lastRequest, 0);
	delete lastRequest;

	emit networkReplyTimedOut();
}

