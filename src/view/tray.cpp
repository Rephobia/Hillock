/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov <doomerroman@gmail.com>

 * This file is part of Memedar (flashcard system)
 * Memedar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
