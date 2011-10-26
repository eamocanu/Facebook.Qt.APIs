#ifndef FACEBOOK_H
#define FACEBOOK_H

/**
 * Experimental Facebook APIs
 *
 * Created by Adrian M in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs/downloads
 * Git repository https://github.com/eamocanu/Facebook.Qt.APIs
 */

/* Released under the BSD license
Copyright (c) 2010, Adrian M
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QString>
#include <QtCore>
#include <QtGui>
#include <QtWebKit>
#include <QtNetwork>
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <QCoreApplication>
#include <QByteArray>
#include <QTimer>
#include <QList>

#include "PhotoData.h"
#include "FBNetworkRequest.h"
#include "JSONEvaluator.h"
#include "FBUserManager.h"
#include "FBUser.h"


/* Provides basic APIs for interfacing with facebook from Qt applications 
	For each operation: photo upload, photo publish, log in, an according
	signal is sent.
	If a request timesout, this class emits timedOut()
	
	User of this class can check the status of the photo upload with 
	isPhotoUploadSuccessful() when photoUploadFinished() signal is emitted
	or any time after.

	Now supporting multiple user management.
	*/
class Facebook : public QObject{
	Q_OBJECT

public:
	//enum SEND_METHOD {POST, GET};


signals:
	/* Indicates user logged in and a token was received - ie successful log in */
	void logInFinished();

	/* Indicates ONLY TEXT user data has been retrieved ie: strings. */
	/*private*/ void getTextUserDataFinished();

	/* Indicates when correct URL for the user main photo has been retrieved
		Original URL redirects which is not caught by network manager */
	/*private*/ void mainPhotoUrlLoaded();

	/* Indicates photo upload request was sent and a reply received. 
		For status check use isPhotoUploadSuccessful() */
	void photoUploadFinished();

	/* Indicates photo publish request was sent and a reply received. To check status of
		request use isPhoto isPhotoPublishSuccessful() */
	void photoPublishFinished();
	
	/* Indicates request was sent, but there was no reply received. Status of request is unknown */
	void networkReplyTimedOut();

	/* Indicates user needs to log in before doing any operations */
	void sessionNeeded();

	/* Indicates multiple users are logged in. Set one as the main user and retry request */
	void multipleUsersLoggedIn();


private:
	//PERMISSIONS: publish_stream,user_photos,create_event,offline_access,read_stream,email, MORE
	//https://graph.facebook.com/oauth/authorize?client_id=112189648850879&redirect_uri=http://www.facebook.com/connect/login_success.html&type=user_agent&display=popup
	#define REDIRECT_URI "http://www.facebook.com/connect/login_success.html"
	#define URL "https://graph.facebook.com/oauth/authorize?client_id=%1&redirect_uri=%2&type=user_agent&display=%3&scope=publish_stream,user_photos,read_stream,email"

	#define ACCESS_TOKEN "access_token"
	
	//FB errors contained in network replies
	#define	TOKEN_EXPIRED_ERROR "Error validating access token."
	#define	TOKEN_MISSING_ERROR "An active access token must be used to query information about the current user."

	//network request timeout time in seconds
	#define REQUEST_TIMEOUT 30
	
	#define BASE_URL "https://graph.facebook.com"


private:
	//FB log in variables
	QString display;
	QString redirectURI;
	QString clientID;
	QString loginUrl;

	//FB active user variables
	QString authToken;//current FB user
	QString crtUserProfileUrl;//current FB user-used as key to retrieve user data
	
	//status of requests 
	FBNetworkRequest::STATUS logInStatus;
	FBNetworkRequest::STATUS photoUploadStatus;
	FBNetworkRequest::STATUS photoPublishStatus;
	FBNetworkRequest::STATUS userInfoRetrievedStatus;//after log in by using /me 
	FBNetworkRequest::STATUS mainPhotoRetrievedStatus;

	//for sending requests
	QNetworkAccessManager networkManager;

	//for logging in through browser
	QWebView *webView;
	QWebFrame* frame;
	
	//trigger timeouts of request-reply communication
	QTimer requestTimer;
	QMutex requestListMutex;

	//all requests go in this queue to be sent
	QVector<FBNetworkRequest*> requestQueue;

	//Manages users currently logged in
	FBUserManager userManager;

	//To allow to return pointers to signals
	typedef void (Facebook::*Signal)();


private:

	/* Add request to queue to be sent. Request will be sent when it reaches head of queue */
	void addRequestToQueue(FBNetworkRequest *request);
	
	/* Sends a request via network manager */
	void sendMessage(FBNetworkRequest *request);

	/* Parses reply data and emits signals for each request type 
		lastRequest: reply data is parsed according to info stored in this request 
		Returns signals for the request sent */
	Signal parseReplyData(FBNetworkRequest *lastRequest, QByteArray replyData);

	/* See how many users are logged in.
		If no user is logged in, it forwards to logIn()
		If more users are logged in, emits multipleUsersLoggedIn() */
	void checkUsersLoggedIn();

	/* Issue request for retrieving data of user currently logged in.
		When done emits loadUserDataFinished()
		Called automatically during log in */
	void getCurrentUserData();

	


public:
	/* Display of device this app runs on */ //FB is still buggy on this
	struct display_type {
		static QString TOUCH_DEVICE(){ return "touch"; }
		static QString POPUP(){ return "popup"; }
	};
	
	/*  clientID: facebook application ID on whose behalf to act
		redirectURI: facebook needs to redirect user to some page after login
					 by default it uses REDIRECT_URI because the browser window is 
					 hidden so it doesn't matter right now
		display: touchscreen or popup. Since touch is buggy it defaults to popup */
	Facebook(QString clientID, QString redirectURI=REDIRECT_URI, QString display=display_type::POPUP());
	~Facebook(void);
	
	
	/* Logs into FB and retrieves user data (email, photo Url, etc). Emits logInFinished() when done */
	void logIn();

	/* Upload photo to APPLICATION_NAME album. ie: uses name of whatever your facebook app is called
		title: photo caption
		filePath: location of file

		Sometimes user still needs to approve photo before appearing publicly in the album.
		If a photo is removed from the wall, all subsequent posts WILL NOT appear on wall */
	void uploadPhoto(const QString &title, const QString &filePath);

	/* Upload photo to APPLICATION_NAME album. ie: uses name of whatever your facebook app is called
		title: photo caption
		photoData: photo file bytes

		Sometimes user still needs to approve photo before appearing publicly in the album.
		If a photo is removed from the wall, all subsequent posts WILL NOT appear on wall */
	void uploadPhoto(const QString &title, const QByteArray *photoData);

	/* Publishes photo to user's wall based on PhotoData object. 
		Photo must already be uploaded on a server */
	void publishPhoto(const PhotoData *photoData);


	/* Returns status of login operation */
	bool isLoginSuccessful();
	
	/* Returns status of photo upload operation */
	bool isPhotoUploadSuccessful();

	/* Returns status of photo publishing operation */
	bool isPhotoPublishSuccessful();
	

	/* Returns all users who have logged in */
	QList<FBUser*> getActiveUsers();
	
	/* Returns currently active user: Last user which logged in is the current user */
	FBUser* getCurrentlyActiveUser();

	/* Set active user the user corresponding to mainPhotoUrl */
	void setCurrentlyActiveUser(QString mainPhotoUrl);

	/* Returns numbers of users currently logged into facebook */
	int getNumUsers();


private slots:
	/* Called when browser loads a new URL.
		The URL may contain the authentication token sent from FB */
	void urlChanged(const QUrl& qurl);

	/* Called when reply is sent back from facebook. Used with network manager 
		Request at head of queue is dequeued and based on it, the information
		received in the reply is interpreted.
		If request was lost from the queue, returns silently with debug error message 
		Emits signals for each request type */
	void parseNetworkReply(QNetworkReply* reply);
	
	/* Called by timer when network reply times out. Emits networkReplyTimedOut() */
	void onReplyTimeout();

	/* Called after login token and user text data is received. 
		Retrieves and stores user main photo with user data */
	void getMainPhotoUrl();

	/* Called after the main photo URL has been forwarded to the correct on by facebook */
	void loadMainPhoto();
};

#endif
