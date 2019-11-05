#ifndef HILLOCK_HOTKEY_HPP
#define HILLOCK_HOTKEY_HPP


#include <QKeySequenceEdit>

namespace view {
	class hotkey;
}

class QWidget;
class QKeyEvent;
class QKeySequence;


class view::hotkey : public QKeySequenceEdit
{
public:
	hotkey(QWidget* parent);
	void register_button();
	bool check_button(void* message);
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
protected:
	unsigned int mod_key(const QKeySequence& sequence);
	unsigned int hot_key(const QKeySequence& sequence);
protected:
	QWidget* m_parent;
		
};


#endif // HILLOCK_HOTKEY_HPP
