#ifndef FBUSER_H
#define FBUSER_H

/**
 * Experimental Facebook APIs
 *
 * Created by Adrian M in 2010
 *
 * Downloaded from https://github.com/eamocanu/Facebook.Qt.APIs/downloads
 * Git repository https://github.com/eamocanu/Facebook.Qt.APIs
 */

/* Released under the BSD license
	Copyright 2010 Adrian M. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Adrian M ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Adrian M.
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
