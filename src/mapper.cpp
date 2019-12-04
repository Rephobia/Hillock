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
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include "mapper.hpp"
#include "runners.hpp"
#include "hotkey.hpp"


using data::mapper;

mapper::mapper(QWidget* mainwindow)
	: m_mainwindow {mainwindow}
{ ;}

void mapper::read(model::runners* runners, hotkey::quit& quithotkey)
{
	QFile file {mapper::FILE_NAME};

	if (not file.exists()) {
		return;
	}
	
	if (not file.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(m_mainwindow, "mapper::read", "Can't open the file "
		                      + mapper::FILE_NAME);
		return;
	}
	
	QJsonParseError parse_error;
	QJsonDocument document {QJsonDocument::fromJson(file.readAll(), &parse_error)};
		
	if (parse_error.error != QJsonParseError::NoError) {

		QMessageBox::critical(m_mainwindow, "mapper::read", "parse error "
		                      + mapper::FILE_NAME + ": " + parse_error.errorString());
		return;
	}
	
	if (not document.isObject()) {
		QMessageBox::critical(m_mainwindow, "mapper::read", "parse error "
		                      + mapper::FILE_NAME + " isn't object");
		return;
	}

	mapper::read(document, runners, quithotkey);
}

void mapper::read(const QJsonDocument& document, model::runners* runners, hotkey::quit& quithotkey)
{
	QJsonObject jobject {document.object()};
		
	for (QJsonValueRef e : jobject[mapper::RUNNERS].toArray()) {
		runners->add(e.toString());
	}

	QJsonObject::iterator quit {jobject.find(mapper::QUIT)};

	if (quit != jobject.end()) {
		quithotkey.register_key(quit.value().toString());
	}

	m_jobject = std::move(jobject);		
}

void mapper::append_runner(const QString& filepath)
{
	QJsonObject new_jobject {m_jobject};

	QJsonObject::iterator runners_it {new_jobject.find(mapper::RUNNERS)};
	
	if (runners_it != new_jobject.end()) {

		// Be careful, you must not use uniform init for QJsonArray {QJsonValue.toArray()}.
		// Use assign QJsonarray = QJsonValue::toArray();
		// this is GCC bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92400
		// Qt bugtracker https://bugreports.qt.io/browse/QTBUG-79780
		
		QJsonArray runners = runners_it->toArray();

		runners.append(filepath);

		*runners_it = runners;
	}
	else {

		new_jobject.insert(mapper::RUNNERS, QJsonArray {filepath});

	}

	mapper::write(m_jobject, std::move(new_jobject));
}

void mapper::remove_runner(const QString& filepath)
{
	QJsonObject new_jobject {m_jobject};

	QJsonObject::iterator runners_it {new_jobject.find(mapper::RUNNERS)};

	if (runners_it != new_jobject.end()) {

		// Be careful, you must not use uniform init for QJsonArray {QJsonValue.toArray()}.
		// Use assign QJsonarray = QJsonValue::toArray();
		// this is GCC bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92400
		// Qt bugtracker https://bit.ly/2O0YQmN
		
		QJsonArray runners = runners_it->toArray();
		
		for (QJsonArray::size_type i = runners.size(); i--;) {
		
			if (runners[i] == filepath) {

				runners.removeAt(i);
				*runners_it = runners;
				break;
			}
		}
	}
	
	mapper::write(m_jobject, std::move(new_jobject));
}

void mapper::write(QJsonObject& old_object, QJsonObject&& new_object)
{
	QFile file {mapper::FILE_NAME};

	if (file.open(QIODevice::WriteOnly)) {

		file.resize(0);
		file.write(QJsonDocument(new_object).toJson(QJsonDocument::Indented));
		
		old_object = std::move(new_object);
	}
	else {
		QMessageBox::critical(m_mainwindow, "mapper::write", "Can't write the file "
		                      + mapper::FILE_NAME);

	}
}

void mapper::set_quithotkey(const QKeySequence& quithotkey)
{
	QJsonObject new_jobject {m_jobject};	
		
	QJsonObject::iterator quit {new_jobject.find(mapper::QUIT)};

	if (quit != new_jobject.end()) {
		*quit = quithotkey.toString();
	} else {
		new_jobject.insert(mapper::QUIT, QJsonValue {quithotkey.toString()});
	}
	
	mapper::write(m_jobject, std::move(new_jobject));
}
