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
#ifndef HILLOCK_HOTKEY_HPP
#define HILLOCK_HOTKEY_HPP


#include <QKeySequence>
#include <QObject>

class QWidget;
class QKeySequence;

namespace hotkey {
	
	class quit;
	
	bool check_button(void* message);
}

class hotkey::quit : public QObject
{
	Q_OBJECT
public:
	quit(QWidget* mainwindow);
	const QKeySequence& sequence() const;
	void register_key(const QKeySequence& sequence);
signals:
	void registered(const QKeySequence& sequence);
protected:
	QKeySequence m_sequence;
	QWidget* m_mainwindow;
	int m_keyid {100};
};

#endif // HILLOCK_HOTKEY_HPP
