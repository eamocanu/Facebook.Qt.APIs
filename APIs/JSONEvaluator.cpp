/**
 * Experimental Facebook APIs
 *
 * Created by Adrian Mocanu in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs
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
