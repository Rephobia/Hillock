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
	                 [&mapper](const QString& filepath)
	                 {
		                 mapper.append_runner(filepath);
	                 });

	QObject::connect(runners, &view::runners_decorator::remove_runner,
	                 [&mapper](const QString& filepath)
	                 {
		                 mapper.remove_runner(filepath);
	                 });
	
	QObject::connect(&quitkey, &hotkey::quit::registered,
	                 [&mapper](const QKeySequence& sequence)
	                 {
		                 mapper.set_quithotkey(sequence);
	                 });

	QObject::connect(mainwindow.quit_keyedit, &view::keyedit::key_edited,
	                 [&quitkey](const QKeySequence& quithotkey)
	                 {
		                 quitkey.register_key(quithotkey);
	                 });

	mapper.read(runners, quitkey);
	
	mainwindow.quit_keyedit->setKeySequence(quitkey.sequence());
	mainwindow.show();
	
	return app.exec();
}
