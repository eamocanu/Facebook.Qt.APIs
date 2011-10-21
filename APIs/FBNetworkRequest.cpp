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

#include "FBNetworkRequest.h"

FBNetworkRequest::FBNetworkRequest(QString urlPath, STATUS *sendStatus, SEND_METHOD sendMethod) : 
	sendMethod(sendMethod){
	status= sendStatus;
	jsonReply= false;
	postData=0;

	QUrl url(BASE_URL);
	url.setPath(urlPath);
/*
	if (requestType == GET_USER_DATA_REQUEST){
		url.setPath(USER_DATA);
	} else if (requestType == PHOTO_UPLOAD){
		url.setPath(WALL_PHOTOS_PATH);
	} else if (requestType == PHOTO_PUBLISH){
		url.setPath(WALL_PUBLISH_PATH);
	} else if (requestType == GET_MAIN_PHOTO){
		url.setPath(USER_MAIN_PHOTO);
	}
*/
	request.setUrl(url);
}

FBNetworkRequest::FBNetworkRequest(){}

FBNetworkRequest::~FBNetworkRequest(void){
}

/* Sets token to be used ONLY with multipart message */
void FBNetworkRequest::setToken(QString authToken){
	this->authToken= authToken;
}

/* Override default URL with user made URL */
void FBNetworkRequest::setUrl(QString newUrl){
	request.setUrl(newUrl);
}

bool FBNetworkRequest::isPost(){
	return sendMethod==POST;
}

bool FBNetworkRequest::isGet(){
	return sendMethod==GET;
}

bool FBNetworkRequest::isSuccessful(){
	return (*status == SUCCESS);
}

void FBNetworkRequest::setStatus(STATUS newStatus){
	*status= newStatus;
}

void FBNetworkRequest::addPhotoPostData(const QString &token, const QByteArray *postData, const QString &caption){
	//if (sendMethod==POST){
	//this->postData= postData;
	//}
	this->authToken= token;
	createMultipartPostMessage(postData, caption);
	createMultipartPostMessageHeader();
}

void FBNetworkRequest::addTextPostData(const QByteArray *postData){
	this->postData.append(*postData);
}

QByteArray * FBNetworkRequest::getPostData(){
	return &postData;
}

QNetworkRequest * FBNetworkRequest::getNetworkRequest(){
	return &request;
}

void FBNetworkRequest::setExpectingJSONReply(bool jsonReply){
	this->jsonReply= jsonReply;
}

bool FBNetworkRequest::isExpectingJSONReply(){
	return jsonReply;
}

void FBNetworkRequest::setType(REQUEST_TYPE type){
	this->type= type;
}

FBNetworkRequest::REQUEST_TYPE FBNetworkRequest::getType(){
	return type;
}


/* Create header for post message with a photo.
 * Create header ONLY after message body was created. */
void FBNetworkRequest::createMultipartPostMessageHeader(){
	request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
	request.setRawHeader("Accept-Language", "en-us,en;q=0.5");
	request.setRawHeader("Accept-Encoding", "gzip,deflate");
	request.setRawHeader("Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7");
	request.setRawHeader("Keep-Alive", "300");
	request.setRawHeader("Connection", "keep-alive");
	request.setRawHeader("Content-Type",QString("multipart/form-data; boundary="+QString(POST_MSG_BOUNDARY)).toAscii());
	request.setHeader(QNetworkRequest::ContentLengthHeader, postData.size());
}


/* Create post message for uploading photo to facebook 
	storage: the post message is returned in this stream
	photoData: photo bytes
	photoCaption: photo caption */
void FBNetworkRequest::createMultipartPostMessage(const QByteArray *photoData, const QString &photoCaption){
	QByteArray *storage = &(this->postData);

	storage->append("--"+QString(POST_MSG_BOUNDARY)+"\r\n");
	storage->append("Content-Disposition: form-data; name=\"access_token\"\r\n\r\n");
	storage->append(authToken +"\r\n");
	
	storage->append("--"+QString(POST_MSG_BOUNDARY)+"\r\n");
	storage->append("Content-Disposition: form-data; name=\"message\"\r\n\r\n");
	storage->append(photoCaption);
	storage->append("\r\n");

	storage->append("--"+QString(POST_MSG_BOUNDARY)+"\r\n");
	storage->append("Content-Disposition: form-data; name=\"name\"; filename=\"somepicture.jpg\"\r\n");
	storage->append("Content-Type: image/jpg\r\n\r\n");
	storage->append(*photoData);
	storage->append("\r\n");

	storage->append("--"+QString(POST_MSG_BOUNDARY)+"--\r\n");
}
