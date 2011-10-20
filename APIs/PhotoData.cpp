/**
 * Experimental Facebook APIs
 *
 * Created by Adrian Mocanu in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs
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
