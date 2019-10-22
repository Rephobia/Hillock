#include <QApplication>
#include <QString>

#include "file.hpp"
#include "runner.hpp"
#include "mainwindow.h"


int main(int argc, char* argv[])
{
	QApplication app {argc, argv};

	auto runners {new view::runners {}};
	
	model::dal::read(runners);
	
	view::mainwindow w {runners};
	w.show();
	
	return app.exec();
}
