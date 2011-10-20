#ifndef UIFBUser_H
#define UIFBUser_H


#include <QLabel>
#include <QObject>
#include <QSize>
#include <QWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <QGroupBox>


class UIFBUser : public QWidget {
		Q_OBJECT

public:
	UIFBUser(QWidget *parent = 0);
	~UIFBUser(void);
	
	void setUserPhoto(QByteArray *data);
	void setUserName(QString name);
	void setUserLocation(QString location);
	

private:
	void init();


private:
	QLabel photoLabel, nameLabel, locationLabel;
	//QLabel *locationLabel;
	QPixmap image;
	QVBoxLayout *layout;
	QGroupBox *userDataGroup;

};

#endif