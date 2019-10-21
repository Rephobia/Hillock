#include <QApplication>
#include <QString>

#include "file.hpp"
#include "runner.hpp"
#include "mainwindow.h"


int main(int argc, char* argv[])
{
	QApplication app {argc, argv};

	auto runners {model::dal::read()};       
	
	view::mainwindow w {runners};
	w.show();
	
	return app.exec();
}
