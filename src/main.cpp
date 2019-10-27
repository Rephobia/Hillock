#include <QApplication>
#include <QString>

#include "file.hpp"
#include "runner.hpp"
#include "mainwindow.h"


int main(int argc, char* argv[])
{
	QApplication app {argc, argv};
	QCoreApplication::addLibraryPath("./");
	auto runners {new view::runners {}};
	
	model::dal::read(runners);
	
	view::mainwindow w {runners};

	QObject::connect(&w, &view::mainwindow::new_runner,
	                 model::dal::append);


	
	w.show();
	
	return app.exec();
}
