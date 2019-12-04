/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

 * This file is part of Memedar (flashcard system)
 * Memedar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileDialog>
#include <QDir>

#include "view/mainwindow.h"
#include "./view/ui_mainwindow.h"
#include "view/keyedit.hpp"
#include "view/runners_decorator.hpp"
#include "view/tray.hpp"

#include "hotkey.hpp"


using view::mainwindow;
#include <QMessageBox>
mainwindow::mainwindow()
	: runners      {new view::runners_decorator {}}
	, quit_keyedit {new view::keyedit {}}
	, ui           {new Ui::MainWindow {}}
{
	ui->setupUi(this);
	QMainWindow::setWindowTitle(QStringLiteral("Hillock")); // this line have to be after ui->setupUi(this)

	ui->scrollArea->setWidget(runners);
	ui->scrollArea->setWidgetResizable(true);
	ui->key_layout->addWidget(quit_keyedit);
	
	QObject::connect(ui->run_button, &QPushButton::clicked,
	                 [this]()
	                 {
		                 runners->run();
		                 QWidget::hide();
	                 });

	QObject::connect(ui->add_button, &QPushButton::clicked,
	                 [this]()
	                 {

		                 auto filename {QFileDialog::getOpenFileName(this,
		                                                             "Choose a file",
		                                                             QDir::homePath(),
		                                                             QString {},
		                                                             nullptr,
		                                                             QFileDialog::DontResolveSymlinks)};
		                 if (not filename.isEmpty()) {
			                 runners->add(std::move(filename));
		                 }
	                 });
	
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
		runners->add(std::move(filepath));
	}
}

bool mainwindow::nativeEvent([[maybe_unused]] const QByteArray& eventType,
                             void* message,
                             [[maybe_unused]] long* result)
{
	return hotkey::check_button(message);
}
