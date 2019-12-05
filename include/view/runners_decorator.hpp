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
#ifndef HILLOCK_VIEW_RUNNERS_DECORATOR_HPP
#define HILLOCK_VIEW_RUNNERS_DECORATOR_HPP


#include <QWidget>

#include "runners.hpp"


class QVBoxLayout;
class QPushButton;

namespace view {
	class runners_decorator;
}


class view::runners_decorator : public QWidget
                              , public model::runners
{
	Q_OBJECT
public:
	runners_decorator();
	model::filepath& add(QString&& path) override;
signals:
	void new_runner(const QString& filepath);
	void remove_runner(const QString& filepath);
protected:
	class runner;
	void make_runner_widget(model::filepath& filepath);
	void remove_widget(QString&& path);
protected:
	QVBoxLayout* m_layout;
};


class view::runners_decorator::runner : public QWidget
{
public:
	runner(model::filepath& filepath, QWidget* parent);
	
	QPushButton* remove;
private:
	QWidget* make_item(model::filepath& filepath);
	QWidget* make_separator();
};

#endif // HILLOCK_VIEW_RUNNERS_DECORATOR_HPP
