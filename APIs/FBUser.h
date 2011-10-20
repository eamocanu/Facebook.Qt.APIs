#ifndef FBUSER_H
#define FBUSER_H

/**
 * Experimental Facebook APIs
 *
 * Created by Adrian Mocanu in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs
 */

#include <QString>
#include <QByteArray>

//TODO change into a class and add dtor to delete mainPhoto

/* Holds facebook user data */
typedef struct FBUser {
	QString name;
	QString email;
	QString token;
	QString location;
	QString mainPhotoUrl;//can be used as key
	QString profileUrl;
	QByteArray *mainPhoto;
} FBUser;

#endif
