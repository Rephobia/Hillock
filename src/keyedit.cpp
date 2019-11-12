#include <QKeyEvent>

#include "keyedit.hpp"


using view::keyedit;

void keyedit::keyPressEvent(QKeyEvent* event)
{
	QKeySequenceEdit::keyPressEvent(event);    
	QKeySequenceEdit::setKeySequence(keySequence()); // single key sequence
}

void keyedit::keyReleaseEvent(QKeyEvent* event)
{
	QKeySequenceEdit::keyReleaseEvent(event);
	emit editingFinished();
	QWidget::clearFocus();
}
