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
#ifndef HILLOCK_MAPPER_HPP
#define HILLOCK_MAPPER_HPP


#include <QString>
#include <QJsonObject>

namespace model {
	class runners;
}

namespace data {
	class mapper;
}

namespace hotkey {
	class quit;
}


class data::mapper : public QObject
{
	Q_OBJECT
public:
	mapper(QWidget* mainwindow);
	
	void read(model::runners* runners, hotkey::quit& quithotkey);
	void append_runner(const QString& filepath);
	void set_quithotkey(const QKeySequence& quithotkey);
	
	void remove_runner(const QString& filepath);
protected:
	void read(const QJsonDocument& document, model::runners* runners, hotkey::quit& quithotkey);
	// assign new object to old object if new object was written to json file
	void write(QJsonObject& old_object, QJsonObject&& new_object);
	
	QJsonObject m_jobject;
	QWidget* m_mainwindow;
protected:
	inline static const QString FILE_NAME {QStringLiteral("runners.json")};
	inline static const QString RUNNERS {QStringLiteral("runners")};
	inline static const QString QUIT {QStringLiteral("QUIT")};
};


#endif // HILLOCK_MAPPER_HPP
