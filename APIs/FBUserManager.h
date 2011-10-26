#ifndef FBUSERMANAGER_H
#define FBUSERMANAGER_H

/**
 * Experimental Facebook APIs
 *
 * Created by Adrian M in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs/downloads
 * Git repository https://github.com/eamocanu/Facebook.Qt.APIs
 */

/* Released under the BSD license
Copyright (c) 2010, Adrian M
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
