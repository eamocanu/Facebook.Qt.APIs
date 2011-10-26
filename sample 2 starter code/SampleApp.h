
#include <QObject>
//#include "PhotoUploader.h"

//#include "FBUserUI.h"
#include "FBUser.h"

#include <QtNetwork>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QByteArray>
#include "UIFBUser.h"
#include <QWidget>
#include "UIFBmain.h"


class Facebook;
//class PhotoUploader;

class SampleApp : QObject {
    Q_OBJECT


public:

    SampleApp();
	~SampleApp();


private:
	Facebook *face;
	QString localPhotoPath;
	//PhotoUploader *photoUploader;

	QNetworkAccessManager networkManager;
	UIFBUser fbui;
	UIFBUser *fbui2;
	UIFBUser *fbui3;
	UIFBmain *window;

private slots:
	void publishPhoto();
	void uploadFinished();
	void parseNetworkReply(QNetworkReply* reply);
	void doStuff();

};

