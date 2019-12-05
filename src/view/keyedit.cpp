/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov <doomerroman@gmail.com>

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
#include <QKeyEvent>

#include "view/keyedit.hpp"


using view::keyedit;

keyedit::keyedit()
{
	this->setFixedWidth(90);
}
void keyedit::keyPressEvent(QKeyEvent* event)
{
	QKeySequenceEdit::keyPressEvent(event);    
	QKeySequenceEdit::setKeySequence(QKeySequenceEdit::keySequence()); // single key sequence
}

void keyedit::keyReleaseEvent(QKeyEvent* event)
{
	QKeySequenceEdit::keyReleaseEvent(event);
	emit key_edited(QKeySequenceEdit::keySequence());
	QWidget::clearFocus();
}
