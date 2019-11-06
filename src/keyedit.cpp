#include "keyedit.hpp"

using view::keyedit;

QKeySequence keyedit::sequence()
{
	return keySequence();
}

void keyedit::keyPressEvent(QKeyEvent *event)
{
	QKeySequenceEdit::keyPressEvent(event);
    
	QKeySequenceEdit::setKeySequence(keySequence()); // single key sequence
}

void keyedit::keyReleaseEvent([[maybe_unused]] QKeyEvent *event)
{
	emit QKeySequenceEdit::editingFinished();
	QWidget::clearFocus();
}
