#include <QDragEnterEvent>
#include <QMimeData>
#include <QSystemTrayIcon>

#include "view/mainwindow.h"
#include "./view/ui_mainwindow.h"
#include "view/keyedit.hpp"
#include "view/runners_decorator.hpp"
#include "view/tray.hpp"

#include "hotkey.hpp"


using view::mainwindow;

mainwindow::mainwindow(view::runners_decorator* runners)
	: m_runners      {runners}
	, m_quit_keyedit {new view::keyedit {}}
	, ui             {new Ui::MainWindow {}}
{
	ui->setupUi(this);
	QMainWindow::setWindowTitle(QStringLiteral("Hillock")); // this line have to be after ui->setupUi(this)

	ui->scrollArea->setWidget(m_runners);
	ui->scrollArea->setWidgetResizable(true);
	
	QObject::connect(ui->run_button, &QPushButton::clicked,
	                 [this]()
	                 {
		                 m_runners->run();
		                 QWidget::hide();
	                 });

	QObject::connect(m_quit_keyedit, &QKeySequenceEdit::editingFinished,
	                 [this]()
	                 {
		                 emit quit_edited(m_quit_keyedit->keySequence());
	                 });

	ui->key_layout->addWidget(m_quit_keyedit);

	auto tray {new view::tray {this}};
	
	QObject::connect(tray, &view::tray::triggered,
	                 this, &view::mainwindow::toggle_show);

	QObject::connect(tray->quit, &QAction::triggered,
	                 this, &QWidget::close);
	QObject::connect(tray->restore, &QAction::triggered,
	                 this, &QWidget::show);
		
	setAcceptDrops(true);
}

mainwindow::~mainwindow()
{
	delete ui;
}

void mainwindow::toggle_show()
{
	if (QWidget::isVisible()) {
		QWidget::hide();
	}
	else {
		QWidget::activateWindow();
		QWidget::show();
	}
}

void mainwindow::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::WindowStateChange) {

		if (QWidget::isMinimized()) {
			QWidget::showNormal(); // without it windows doesn't show, after minimize;
			QWidget::hide();
			event->ignore();
		}

	}
	
	QMainWindow::changeEvent(event);
}

void mainwindow::set_quithotkey(const QKeySequence& quithotkey)
{
	m_quit_keyedit->setKeySequence(quithotkey);
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
