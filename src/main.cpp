#include <QApplication>
#include <QString>

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

	QKeySequence quit {};

	data::mapper mapper {};
	mapper.read(runners, quit);

	
	view::mainwindow w {runners, std::move(quit)};

	QObject::connect(&w, &view::mainwindow::new_runner,
	                 [&mapper](const QString& filepath)
	                 {
		                 mapper.append_runner(filepath);
	                 });

	QObject::connect(runners, &view::runners::remove_runner,
	                 [&mapper](const QString& filepath)
	                 {
		                 mapper.remove_runner(filepath);
	                 });
	
	QObject::connect(&hotkey::quit::bell::instance(), &hotkey::quit::bell::reg_hotkey,
	                 [&mapper](const QKeySequence& sequence)
	                 {
		                 mapper.set_quithotkey(sequence);
	                 });
	
	w.show();
	
	return app.exec();
}
