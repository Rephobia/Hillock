#ifndef HILLOCK_KEYEDIT_HPP
#define HILLOCK_KEYEDIT_HPP


#include <QKeySequenceEdit>

namespace view {
	class keyedit;
}


class view::keyedit : public QKeySequenceEdit
{
private:
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
};


#endif // HILLOCK_KEYEDIT_HPP
