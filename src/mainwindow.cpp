#include <QDragEnterEvent>
#include <QMimeData>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "runner.hpp"
#include "file.hpp"

using view::mainwindow;

mainwindow::mainwindow(view::runners* runners,
                       QWidget* parent)
	: QMainWindow {parent}
	, ui          {new Ui::MainWindow {}}
	, m_runners   {runners}
{
	ui->setupUi(this);
	QMainWindow::setWindowTitle("Hillock"); // this line have to be after ui->setupUi(this)

	ui->scrollArea->setWidget(m_runners);
	ui->scrollArea->setWidgetResizable(true);
	
	QObject::connect(ui->run_button, &QPushButton::clicked,
	                 runners, &view::runners::run);

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
		QString file {url.toLocalFile()};
		model::dal::append(file);
		m_runners->add(std::move(file));
		
	}
}
