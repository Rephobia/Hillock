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
