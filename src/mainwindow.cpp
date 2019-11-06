#include <QDragEnterEvent>
#include <QMimeData>
#include <QCoreApplication>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "runner.hpp"
#include "keyedit.hpp"
#include "hotkey.hpp"


#include <QKeyEvent>


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

	auto keyedit {new view::keyedit {}};
	
	QObject::connect(keyedit, QKeySequenceEdit::editingFinished,
	                 [this, keyedit]()
	                 {
		                 hotkey::quit::register_button(this, keyedit->sequence());
	                 });
	
	ui->key_layout->addWidget(keyedit);
	
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
		QString filepath {url.toLocalFile()};
		emit new_runner(filepath);
		m_runners->add(std::move(filepath));
	}
}

bool mainwindow::nativeEvent([[maybe_unused]] const QByteArray& eventType,
                             void* message,
                             [[maybe_unused]] long* result)
{
	return hotkey::check_button(message);
}
