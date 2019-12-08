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
#include <QApplication>
#include <QString>

#include "mapper.hpp"
#include "view/runners_decorator.hpp"
#include "view/mainwindow.h"
#include "view/keyedit.hpp"

#include "hotkey.hpp"

int main(int argc, char* argv[])
{	
	QApplication app {argc, argv};
	QCoreApplication::addLibraryPath("./");
	QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins");

	view::mainwindow mainwindow {};
	
	hotkey::quit quitkey {&mainwindow};
	data::mapper mapper {&mainwindow};
	
	QObject::connect(mainwindow.runners, &view::runners_decorator::new_runner,
	                 &mapper, &data::mapper::append_runner);

	QObject::connect(mainwindow.runners, &view::runners_decorator::remove_runner,
	                 &mapper, &data::mapper::remove_runner);

	QObject::connect(&quitkey, &hotkey::quit::registered,
	                 &mapper, &data::mapper::set_quithotkey);

	QObject::connect(mainwindow.quit_keyedit, &view::keyedit::key_edited,
	                 &quitkey, &hotkey::quit::register_key);

	mapper.read(mainwindow.runners, quitkey);
	
	mainwindow.quit_keyedit->setKeySequence(quitkey.sequence());
	
	mainwindow.show();
	
	return app.exec();
}
