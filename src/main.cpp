#include <QApplication>
#include <QString>
#include <QKeyEvent>

#include "mapper.hpp"
#include "runner.hpp"
#include "moc_runner.cpp"
#include "moc_hotkey.cpp"
#include "mainwindow.h"


int main(int argc, char* argv[])
{	
	QApplication app {argc, argv};
	QCoreApplication::addLibraryPath("./");

	auto runners {new view::runners {}};

	view::mainwindow mainwindow {runners};
	
	hotkey::quit quitkey {&mainwindow};
	
	data::mapper mapper {};
	
	QObject::connect(&mainwindow, &view::mainwindow::new_runner,
	                 [&mapper](const QString& filepath)
	                 {
		                 mapper.append_runner(filepath);
	                 });

	QObject::connect(runners, &view::runners::remove_runner,
	                 [&mapper](const QString& filepath)
	                 {
		                 mapper.remove_runner(filepath);
	                 });
	
	QObject::connect(&quitkey, &hotkey::quit::registered,
	                 [&mapper](const QKeySequence& sequence)
	                 {
		                 mapper.set_quithotkey(sequence);
	                 });

	QObject::connect(&mainwindow, &view::mainwindow::quit_edited,
	                 [&quitkey](const QKeySequence& quithotkey)
	                 {
		                 quitkey.register_key(quithotkey);
	                 });

	mapper.read(runners, quitkey);
	mainwindow.set_quithotkey(quitkey.sequence());
	mainwindow.show();
	
	return app.exec();
}
