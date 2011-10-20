
#include <QObject>
//#include "PhotoUploader.h"

class Facebook;

class SampleApp : QObject {
    Q_OBJECT


public:

    SampleApp();
	~SampleApp();


private:
	Facebook *face;
	QString localPhotoPath;
	//PhotoUploader *photoUploader;

	#define ROOT_URL "http://internal.elacarteonline.com/elc_api/"

private slots:
	void publishPhoto();
	void uploadFinished();

};

