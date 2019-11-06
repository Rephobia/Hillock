#ifndef HILLOCK_HOTKEY_HPP
#define HILLOCK_HOTKEY_HPP


class QWidget;
class QKeySequence;


namespace hotkey {
	bool check_button(void* message);	
}

namespace hotkey::quit {
	void register_button(QWidget* mainwindow, const QKeySequence& sequence);
}

#endif // HILLOCK_HOTKEY_HPP
