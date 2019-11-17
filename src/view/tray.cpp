#include <QMenu>
#include <QWidget>
#include <QAction>

#include "view/tray.hpp"

using view::tray;

tray::tray(QWidget* parent)
	: QSystemTrayIcon {parent}
	, quit            {new QAction {"Quit", parent}}
	, restore         {new QAction {"Restore", parent}}
	  
{
	QSystemTrayIcon::setToolTip(QStringLiteral("Hillock"));
	QSystemTrayIcon::setIcon(QIcon {QStringLiteral(":/icon32x32.ico")});
	
	auto menu {new QMenu {parent}};

	menu->addAction(restore);
	menu->addAction(quit);
	
	QSystemTrayIcon::setContextMenu(menu);
	
	QObject::connect(this, &QSystemTrayIcon::activated,
	                 this, &view::tray::icon_activated);
	
	QSystemTrayIcon::show();
}

void view::tray::icon_activated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
		
	case QSystemTrayIcon::Trigger:
		emit triggered();
	default:
		break;
	}

}
