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

	auto runners {new view::runners_decorator {}};

	view::mainwindow mainwindow {runners};
	
	hotkey::quit quitkey {&mainwindow};
	data::mapper mapper {&mainwindow};
	
	QObject::connect(runners, &view::runners_decorator::new_runner,
	                 &mapper, &data::mapper::append_runner);

	QObject::connect(runners, &view::runners_decorator::remove_runner,
	                 &mapper, &data::mapper::remove_runner);

	QObject::connect(&quitkey, &hotkey::quit::registered,
	                 &mapper, &data::mapper::set_quithotkey);

	QObject::connect(mainwindow.quit_keyedit, &view::keyedit::key_edited,
	                 &quitkey, &hotkey::quit::register_key);

	mapper.read(runners, quitkey);
	
	mainwindow.quit_keyedit->setKeySequence(quitkey.sequence());
	mainwindow.show();
	
	return app.exec();
}
