#ifndef HILLOCK_VIEW_TRAY_HPP
#define HILLOCK_VIEW_TRAY_HPP


#include <QSystemTrayIcon>

class QAction;

namespace view {
	class tray;
}


class view::tray : public QSystemTrayIcon
{
	Q_OBJECT
public:
	tray(QWidget* parent);
	void icon_activated(QSystemTrayIcon::ActivationReason reason);

	QAction* quit;
	QAction* restore;
signals:
	void triggered();
	
};

#endif // HILLOCK_VIEW_TRAY_HPP
