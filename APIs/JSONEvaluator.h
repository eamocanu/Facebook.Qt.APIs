#ifndef JSONEVALUATOR_H
#define JSONEVALUATOR_H

/**
 * Experimental Facebook APIs
 *
 * Created by Adrian Mocanu in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs
 */

#include <QString>
#include <QObject>
#include <QWebView>
#include <QWebFrame>


/* Extracts data from JSON objects */
class JSONEvaluator : public QObject {
	Q_OBJECT


private:
	#define THE_VAR "myJSON1"
	#define HEADER "<html><head><script type=\"text/javascript\">var myJSON1; function load() { "
	#define FOOTER "} </script></head><body onload=\"load()\"></body></html>"

	QWebView* webView;
	QWebFrame* fr;
	QString jsContents;
	
	
public:
	JSONEvaluator(void);
	~JSONEvaluator(void);
	
	/* Set JSON data */
	void setJSON(QString jsString);
	
	/* Retrieves field from JSON object or empty string if such field DNE */
	QString getField(QString fieldName);

	/* Retrieves error field from JSON object or empty string if such field DNE */
	QString getErrorMessage();

	/* Retrieves location field from JSON object or empty string if such field DNE */
	QString getLocation();
	
};

#endif
