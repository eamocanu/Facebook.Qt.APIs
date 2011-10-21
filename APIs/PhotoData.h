#ifndef PHOTODATA_H
#define PHOTODATA_H

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

#include <QString>

/* Corresponding FB REST params
	{"name":"%1",postLinkTitle
		"caption":"%2",postTitle
		"description":"%3",postText
		"href":"%4",postLinkUrl
		"media":[{"type":"image","href":"%5","src":"%5"}] postPhotoUrl
	}
	&display=popup&locale=en_US&user_message_prompt=%6 postUserMessagePrompt
		&next=%7 postForwardToPageUrl
*/

/* Corresponding FB GRAPH API params
curl -F 'access_token=...' \
     -F 'message=Check out this funny article' \
     -F 'link=http://www.example.com/article.html' \
     -F 'picture=http://www.example.com/article-thumbnail.jpg' \
     -F 'name=Article Title' \
     -F 'caption=Caption for the link' \
     -F 'description=Longer description of the link' \
     -F 'actions={"name": "View on Zombo", "link": "http://www.zombo.com"}' \
     -F 'privacy={"value": "ALL_FRIENDS"}' \
     -F 'targeting= {"countries":"US","regions":"6,53","locales":"6"}' \
     https://graph.facebook.com/me/feed
*/

/* Class is container of picture post data which is published to the wall */
class PhotoData {

private:
	#define DEFAULT_POST_LINK_TITLE "Created with Adrian's FB APIs for Qt by Nokia"
	#define DEFAULT_POST_TITLE "A better FB experience by Adrian M!"
	#define DEFAULT_POST_TEXT "Try it in your app!"
	#define DEFAULT_POST_LINK_URL "www.facebook.com/fashion.playb0y"
	#define DEFAULT_EMPTY ""

	//only for old REST APIs - required by FB 
	#define DEFAULT_POST_FORWARDTO_PAGE_URL "http://www.facebook.com/connect/login_success.html"
	

public:
	PhotoData(QString postPhotoUrl, QString postUserMessagePrompt,
		QString postLinkTitle= DEFAULT_POST_LINK_TITLE, QString postTitle= DEFAULT_POST_TITLE, 
		QString postText= DEFAULT_POST_TEXT, QString postLinkUrl= DEFAULT_POST_LINK_URL,
		QString postForwardToPageUrl= DEFAULT_POST_FORWARDTO_PAGE_URL
		);

	PhotoData(QString postPhotoUrl, QString postText= DEFAULT_POST_TEXT,
		QString postForwardToPageUrl= DEFAULT_POST_FORWARDTO_PAGE_URL,
		QString postUserMessagePrompt= DEFAULT_EMPTY);

	~PhotoData(void);

	QString postLinkTitle;
	QString postTitle;
	QString postText;
	QString postLinkUrl;
	QString postPhotoUrl;
	QString postForwardToPageUrl;
	QString postUserMessagePrompt;
	
};

#endif
