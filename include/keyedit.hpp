#ifndef HILLOCK_KEYEDIT_HPP
#define HILLOCK_KEYEDIT_HPP


#include <QKeySequenceEdit>

namespace view {
	class keyedit;
}


class view::keyedit : public QKeySequenceEdit
{
public:
	QKeySequence sequence();
	void set_sequence(QKeySequence&& sequence);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
};




#endif // HILLOCK_KEYEDIT_HPP
