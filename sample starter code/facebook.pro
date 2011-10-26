CONFIG += qt debug
TEMPLATE = app
HEADERS = UIFBUser.h UIFBmain.h FBUserUI.h FBNetworkRequest.h FBUserManager.h FBUser.h JSONEvaluator.h SampleApp.h PhotoData.h Facebook.h
SOURCES = FBNetworkRequest.cpp FBUserManager.cpp JSONEvaluator.cpp SampleApp.cpp PhotoData.cpp Facebook.cpp main.cpp
QT += core gui network qtmain webkit
win32:debug {
    CONFIG += console
}
