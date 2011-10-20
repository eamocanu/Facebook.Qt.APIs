#include "UIFBUser.h"
#include <QCheckBox>

UIFBUser::UIFBUser(QWidget *parent) : QWidget(parent){
	init();
}

UIFBUser::~UIFBUser(void){
	delete layout;
}


void UIFBUser::init(){
	userDataGroup= new QGroupBox(this);
	layout= new QVBoxLayout(userDataGroup);
	userDataGroup->setLayout(layout);
	
	nameLabel.setParent(this);
	photoLabel.setParent(this);
	locationLabel.setParent(this);

	layout->addWidget(&photoLabel);
	layout->addWidget(&nameLabel);
	layout->addWidget(&locationLabel);

	this->setLayout(layout);//if not set there is nothing showing
	
	//userDataGroup->adjustSize();
}


void UIFBUser::setUserPhoto(QByteArray *data){
	image.loadFromData(*data);
	photoLabel.setPixmap(image);
	/*
	QSize sz1= photoLabel.frameSize();
	QSize sz2= userDataGroup->frameSize();
	int h,w;
	if (sz1.height() > sz2.height())
		h=sz2.height();
	else h = sz1.height();
	if (sz1.width() > sz2.width())
		h=sz2.width();
	else h = sz1.width();

	h+=10;
	w+=10;

	userDataGroup->setFixedSize(h, w);
	//layout->setFixedSize(h, w);
	userDataGroup->adjustSize();
	*/
}


void UIFBUser::setUserName(QString name){
	//this->name= name;
	nameLabel.setText(name);
	userDataGroup->setTitle(name);

		QSize sz1= nameLabel.frameSize();
	QSize sz2= userDataGroup->frameSize();

}


void UIFBUser::setUserLocation(QString location){
	//this->location= location;
	locationLabel.setText(location);

		QSize sz1= locationLabel.frameSize();
	QSize sz2= userDataGroup->frameSize();

}