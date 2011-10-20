/**
 * Experimental Facebook APIs
 *
 * Created by Adrian Mocanu in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs
 */

#include "FBUserManager.h"



FBUserManager::FBUserManager(void){
}

FBUserManager::~FBUserManager(void){
	qDeleteAll(fbUsers.begin(), fbUsers.end());
}


void FBUserManager::addUser(FBUser *fbUser){
	//allow no duplicates
	removeUser(fbUser->profileUrl);
	
	fbUsers.insert(fbUser->profileUrl, fbUser);
}

void FBUserManager::removeUser(QString profileUrl){
	FBUser* user= fbUsers.take(profileUrl);
	delete user;
}


/* Returns number of users logged in */
int FBUserManager::getNumUsers(){
	return fbUsers.size();
}


/* Returns users logged in */
QList<FBUser*> FBUserManager::getUsers(){
	return fbUsers.values();
}


QString FBUserManager::getName(QString profileUrl){
	it= fbUsers.find(profileUrl);
	if (it == fbUsers.end()){
		return 0;
	} else {
		return (*it)->name;
	}
}

QString FBUserManager::getToken(QString profileUrl){
	it= fbUsers.find(profileUrl);
	if (it == fbUsers.end()){
		return 0;
	} else {
		return (*it)->token;
	}
}

QString FBUserManager::getFromLocation(QString profileUrl){
	it= fbUsers.find(profileUrl);
	if (it == fbUsers.end()){
		return 0;
	} else {
		return (*it)->location;
	}
}

QString FBUserManager::getEmail(QString profileUrl){
	it= fbUsers.find(profileUrl);
	if (it == fbUsers.end()){
		return 0;
	} else {
		return (*it)->email;
	}
}

QString FBUserManager::getPhotoURL(QString profileUrl){
	it= fbUsers.find(profileUrl);
	if (it == fbUsers.end()){
		return 0;
	} else {
		return (*it)->mainPhotoUrl;
	}
}

FBUser* FBUserManager::getUser(QString profileUrl){
	//return *fbUsers.find(profileUrl);
	it= fbUsers.find(profileUrl);
	if (it == fbUsers.end()){
		return 0;
	} else {
		return *it;
	}
}

QString FBUserManager::getUserProfileUrl(QString profileUrl){
	it= fbUsers.find(profileUrl);
	if (it == fbUsers.end()){
		return 0;
	} else {
		return (*it)->profileUrl;
	}
}
