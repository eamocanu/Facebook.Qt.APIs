CONFIG += qt debug
TEMPLATE = app
HEADERS = FBNetworkRequest.h FBUserManager.h FBUser.h JSONEvaluator.h PhotoData.h PhotoUploader.h Facebook.h
SOURCES = FBNetworkRequest.cpp FBUserManager.cpp FBUser.cpp JSONEvaluator.cpp PhotoData.cpp Facebook.cpp
QT += core gui network qtmain webkit
win32:debug {
    CONFIG += console
}
