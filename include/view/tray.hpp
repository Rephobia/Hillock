/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

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
