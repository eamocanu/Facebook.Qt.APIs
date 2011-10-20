#include <QApplication>
#include "SampleApp.h"
#include "UIFBUser.h"

 #include <QtGui>


#if QT_VERSION < 0x0040500
#error You need Qt 4.5 or newer
#endif

int main(int argc, char **argv){

    QApplication app(argc, argv);

    SampleApp w;

    return app.exec();
}
