
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

private slots:
	void publishPhoto();
	void uploadFinished();

};

