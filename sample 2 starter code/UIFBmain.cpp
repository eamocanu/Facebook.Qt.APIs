#include "UIFBmain.h"

UIFBmain::UIFBmain(QWidget *parent) : QWidget(parent){
	chooseUsersGroup= new QGroupBox(this);
	//layout= new QHBoxLayout(this);
	layout= new QHBoxLayout(chooseUsersGroup);
//	this->setLayout(layout);
	chooseUsersGroup->setLayout(layout);
	chooseUsersGroup->setTitle("Choose your facebook ID");
}

UIFBmain::~UIFBmain(void){
	delete chooseUsersGroup;
}


void UIFBmain::addUser(UIFBUser *user){
	user->setParent(this);
	//users.push_back(user);
	layout->addWidget(user);

}
