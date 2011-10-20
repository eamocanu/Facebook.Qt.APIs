
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
//#include <QVector>
#include <QGroupBox>

#include "UIFBUser.h"


class UIFBmain : public QWidget {
		Q_OBJECT

public:
	UIFBmain(QWidget *parent = 0);
	~UIFBmain(void);

	void addUser(UIFBUser *user);


private:
	QHBoxLayout *layout;
	QGroupBox *chooseUsersGroup;

};
