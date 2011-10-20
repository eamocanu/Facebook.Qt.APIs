#ifndef FBUSERMANAGER_H
#define FBUSERMANAGER_H

/**
 * Experimental Facebook APIs
 *
 * Created by Adrian Mocanu in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs
 */

#include <QMap>
#include <QString>
#include <QObject>
#include <QList>

#include "FBUser.h"


/* Manages users logged in and their sessions .
 * Stores FB user data in a map of which key is the URL to that user profile.
 * */
class FBUserManager : public QObject {
	Q_OBJECT

public:
	FBUserManager(void);
	~FBUserManager(void);
	
	void addUser(FBUser *fbUser);
	void removeUser(QString profileUrl);

	/* Returns number of users logged in */
	int getNumUsers();

	/* Returns users logged in */
	QList<FBUser*> getUsers();
	
	QString getName(QString profileUrl);
	QString getToken(QString profileUrl);
	QString getFromLocation(QString profileUrl);
	QString getEmail(QString profileUrl);
	QString getPhotoURL(QString profileUrl);
	QString getUserProfileUrl(QString profileUrl);
	FBUser* getUser(QString profileUrl);
	
	

private:
	QMap<QString, FBUser*>::const_iterator it;
	QMap<QString, FBUser*> fbUsers; //token name etc for users who logged in
	
};

#endif
