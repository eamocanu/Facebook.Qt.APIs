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

#include "PhotoData.h"

PhotoData::PhotoData(QString postPhotoUrl, QString postUserMessagePrompt, 
		QString postLinkTitle, QString postTitle, 
		QString postText, QString postLinkUrl,
		QString postForwardToPageUrl
		):
			postPhotoUrl(postPhotoUrl),postUserMessagePrompt(postUserMessagePrompt),
				postLinkTitle(postLinkTitle),postTitle(postTitle),postText(postText),
				postLinkUrl(postLinkUrl),postForwardToPageUrl(postForwardToPageUrl)				
{}

PhotoData::PhotoData(QString postPhotoUrl, QString postText,
		QString postForwardToPageUrl,
		QString postUserMessagePrompt):
			postPhotoUrl(postPhotoUrl),postText(postText),postForwardToPageUrl(postForwardToPageUrl),
				postUserMessagePrompt(postUserMessagePrompt),
				postLinkTitle(DEFAULT_POST_LINK_TITLE),
				postTitle(DEFAULT_POST_TITLE),
				postLinkUrl(DEFAULT_POST_LINK_URL)
{}

	
PhotoData::~PhotoData(void){
}
