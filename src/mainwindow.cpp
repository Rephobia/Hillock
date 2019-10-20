#include <QDragEnterEvent>
#include <QMimeData>

#include "mainwindow.h"
#include "./ui_mainwindow.h"


using view::mainwindow;

mainwindow::mainwindow(QWidget* parent)
	: QMainWindow {parent}
	, ui          {new Ui::MainWindow {}}
{
	ui->setupUi(this);
	QMainWindow::setWindowTitle("Hillock"); // this line have to be after ui->setupUi(this)
	setAcceptDrops(true);
}

mainwindow::~mainwindow()
{
	delete ui;
}

void mainwindow::dragEnterEvent(QDragEnterEvent* e)
{
	if (e->mimeData()->hasUrls()) {
		e->acceptProposedAction();
	}
}

void mainwindow::dropEvent(QDropEvent* e)
{
	foreach(const QUrl &url, e->mimeData()->urls()) {
		QString fileName {url.toLocalFile()};
	}
}
