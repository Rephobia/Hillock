#include <QDragEnterEvent>
#include <QMimeData>

#include "view/mainwindow.h"
#include "./view/ui_mainwindow.h"
#include "view/keyedit.hpp"
#include "view/runners_decorator.hpp"

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
	                 [this]() { m_runners->run(); });

	QObject::connect(m_quit_keyedit, &QKeySequenceEdit::editingFinished,
	                 [this]()
	                 {
		                 emit quit_edited(m_quit_keyedit->keySequence());
	                 });

	ui->key_layout->addWidget(m_quit_keyedit);
	
	setAcceptDrops(true);
}

mainwindow::~mainwindow()
{
	delete ui;	
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
