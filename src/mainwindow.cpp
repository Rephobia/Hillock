#include <QDragEnterEvent>
#include <QMimeData>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "runner.hpp"

using view::mainwindow;

mainwindow::mainwindow(std::vector<model::runner> runners,
                       QWidget* parent)
	: QMainWindow {parent}
	, ui          {new Ui::MainWindow {}}
{
	ui->setupUi(this);
	QMainWindow::setWindowTitle("Hillock"); // this line have to be after ui->setupUi(this)

	auto container = new QWidget {};
	auto runner_layout {new QVBoxLayout {}};
	container->setLayout(runner_layout);

	for (auto& e: runners) {
		runner_layout->addWidget(new QLabel {e.name()});
	}
	
	ui->scrollArea->setWidget(container);

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
