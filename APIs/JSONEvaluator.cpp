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


#include "JSONEvaluator.h"

JSONEvaluator::JSONEvaluator(void){
	webView= new QWebView(NULL);
	fr= webView->page()->mainFrame();
	jsContents="";
}

JSONEvaluator::~JSONEvaluator(void){
	delete webView;
}


/* Set JSON data */
void JSONEvaluator::setJSON(QString jsString){
	jsContents="";
	
	jsContents.push_front(jsString);
	jsContents.push_front("=");
	jsContents.push_front(THE_VAR);
	jsContents.push_front(HEADER);
	jsContents.push_back(FOOTER);

	fr->setHtml(jsContents);
}


/* Retrieves field from JSON object or empty string if such field DNE */
QString JSONEvaluator::getField(QString fieldName){
	QString queryString(THE_VAR);
	queryString.append("." +fieldName);
	
	return fr->evaluateJavaScript(queryString).toString();
}


/* Retrieves error field from JSON object or empty string if such field DNE */
QString JSONEvaluator::getErrorMessage(){
	QString queryString(THE_VAR);
	queryString.append(".error.message");
	
	return fr->evaluateJavaScript(queryString).toString();
}


/* Retrieves location field from JSON object or empty string if such field DNE */
QString JSONEvaluator::getLocation(){
	QString queryString(THE_VAR);
	queryString.append(".location.name");
	
	return fr->evaluateJavaScript(queryString).toString();
}
