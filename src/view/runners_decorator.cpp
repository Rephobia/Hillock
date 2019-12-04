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
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

#include "view/runners_decorator.hpp"

using view::runners_decorator;

runners_decorator::runners_decorator()
	: m_layout {new QVBoxLayout {this}}
{
	m_layout->setAlignment(Qt::AlignTop);
	m_layout->setSpacing(0);
	m_layout->setMargin(0);
}


model::filepath& runners_decorator::add(QString&& path)
{
	emit new_runner(path);
	
	model::filepath& filepath {model::runners::add(std::move(path))};

	make_runner_widget(filepath);

	return filepath;
}


runners_decorator::runner::runner(model::filepath& filepath, QWidget* parent)
	: QWidget {parent}
	, remove  {new QPushButton {QStringLiteral("remove")}}
{
	remove->setFixedWidth(100);
	remove->setFixedHeight(20);

	auto layout {new QVBoxLayout {this}};
	
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->addWidget(this->make_item(filepath));
	layout->addWidget(this->make_separator());
}

QWidget* runners_decorator::runner::make_item(model::filepath& filepath)
{
	auto item {new QWidget {this}};
	auto layout {new QHBoxLayout {item}};
	
	auto filename {new QLabel {filepath.name()}};
	layout->addWidget(filename);
	layout->addWidget(remove);
				
	return item;
}

QWidget* runners_decorator::runner::make_separator()
{
	auto separator {new QFrame {this}};

	separator->setFrameShape(QFrame::HLine);
	separator->setFrameShadow(QFrame::Sunken);
	separator->setLineWidth(1);
	
	return separator;
}


void runners_decorator::make_runner_widget(model::filepath& filepath)
{
	auto runner {new runners_decorator::runner {filepath, this}};
	
	QObject::connect(runner->remove, &QPushButton::clicked,
	                 [this, runner, &filepath]()
	                 {
		                 emit remove_runner(filepath.path());

		                 runner->hide();
		                 runner->deleteLater();
		                 
		                 model::runners::remove(filepath);
	                 });
	
	m_layout->addWidget(runner);
}
