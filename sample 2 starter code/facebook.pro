CONFIG += qt debug
TEMPLATE = app
HEADERS = UIFBUser.h UIFBmain.h FBUserUI.h FBNetworkRequest.h FBUserManager.h FBUser.h JSONEvaluator.h SampleApp.h PhotoData.h PhotoUploader.h Facebook.h
SOURCES = UIFBUser.cpp UIFBmain.cpp FBUserUI.cpp FBNetworkRequest.cpp FBUserManager.cpp FBUser.cpp JSONEvaluator.cpp SampleApp.cpp PhotoData.cpp PhotoUploader.cpp Facebook.cpp main.cpp
QT += core gui network qtmain webkit
win32:debug {
    CONFIG += console
}
