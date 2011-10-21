#ifndef FBNetworkRequest_H
#define FBNetworkRequest_H

/**
 * Experimental Facebook APIs
 *
 * Created by Adrian M in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs
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

#include <QNetworkRequest>
#include <QByteArray>
#include <QObject>


/* FBNetworkRequest is a wrapper for QNetworkRequest.
	Additionally it holds data to be sent through POST
	It also stores the status of sending the request */
class FBNetworkRequest: public QObject { 
	Q_OBJECT


public:
	enum SEND_METHOD {POST, GET};
	enum STATUS {SUCCESS, FAIL};
	enum REQUEST_TYPE {GET_USER_DATA_REQUEST, PHOTO_UPLOAD, PHOTO_PUBLISH, GET_MAIN_PHOTO, OTHER };
	
	#define BASE_URL "https://graph.facebook.com"


public:
	/*  urlPath: path of facebook url
		sendStatus: will store status of sending this request
		sendMethod: POST or GET supported at the time */
	FBNetworkRequest(QString urlPath, STATUS *sendStatus, SEND_METHOD sendMethod=GET);
	FBNetworkRequest();
	~FBNetworkRequest(void);
	

	/* Sets token to be used ONLY with multipart message */
	void setToken(QString authToken);
	
	/* Is to be sent through POST */
	bool isPost();

	/* Is to be sent through GET */
	bool isGet();

	/* Result of sending request was successful (or not) */
	bool isSuccessful();

	/* Set status resulting from sending this request */
	void setStatus(STATUS newStatus);

	/* Add photo POST data to the request: multipart message */
	void addPhotoPostData(const QString &token, const QByteArray *postData, const QString &caption);

	/* Add text POST data to the request: non multipart message */
	void addTextPostData(const QByteArray *postData);

	/* Get POST data used in the request */
	QByteArray * getPostData();

	/* The network request to piggyback everything being sent */
	QNetworkRequest * getNetworkRequest();

	/* Set to true: when the reply to this request is a JSON object 
				false otherwise */
	void setExpectingJSONReply(bool jsonReply);

	/* Check if reply to request is a JSON object */
	bool isExpectingJSONReply();

	/* Set request type. This is how the sender knows what to emit.
		Can send publish requests, photo upload, user data retrieval, etc */
	void setType(REQUEST_TYPE type);

	/* Returns type of this request */
	REQUEST_TYPE getType();

	/* Override default URL with user made URL */
	void setUrl(QString newUrl);


private:
	/* Create post message for uploading photo to facebook 
		storage: the post message is returned in this stream
		photoData: photo bytes
		photoCaption: photo caption
		*/
	void createMultipartPostMessage(const QByteArray *photoData, const QString &photoCaption);

	/* Create header for post message with a photo
		Create header ONLY after message body was created.
		*/
	void createMultipartPostMessageHeader();


private:
		
	//FB URLs
	#define WALL_PUBLISH_PATH "me/feed"
	#define WALL_PHOTOS_PATH "me/photos"
	//#define FRIENDS_PATH "me/friends"
	#define USER_DATA "me"
	#define USER_MAIN_PHOTO "me/picture"

	//for multipart post message building
	#define POST_MSG_BOUNDARY "---------------------------17673466415141"

	REQUEST_TYPE type;
	bool jsonReply;
	QByteArray postData;
	SEND_METHOD sendMethod;
	STATUS *status;
	QNetworkRequest request;
	QString authToken;
	
};

#endif
