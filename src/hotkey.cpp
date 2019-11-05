#include <windows.h>

#include "hotkey.hpp"
#include <QMessageBox>
#include <QApplication>

using view::hotkey;

hotkey::hotkey(QWidget* parent)
	: QKeySequenceEdit {parent}
	, m_parent {parent}
{
	QObject::connect(this, &QKeySequenceEdit::editingFinished,
	                 this, &hotkey::register_button);
}

void hotkey::register_button()
{
	UnregisterHotKey(HWND(m_parent->winId()), 100);
	if (!RegisterHotKey(HWND(m_parent->winId()), 100, mod_key(keySequence()), hot_key(keySequence()))) {

		QMessageBox::warning(m_parent, "Warning", "Can't register hotkey error: "
		                     + QString::number(GetLastError()));

	} 
}

bool hotkey::check_button(void* message)
{
	auto msg = static_cast<MSG*>(message);
	
	if (msg->message == WM_HOTKEY) {
		QApplication::quit();
		return true;
	}

	return false;
}


void hotkey::keyPressEvent(QKeyEvent *event)
{
	QKeySequenceEdit::keyPressEvent(event);
    
	QKeySequenceEdit::setKeySequence(keySequence()); // single key sequence
}

void hotkey::keyReleaseEvent([[maybe_unused]] QKeyEvent *event)
{
	emit QKeySequenceEdit::editingFinished();	
	QWidget::clearFocus();
}



unsigned int hotkey::mod_key(const QKeySequence& sequence)
{
	QStringList list {sequence.toString().split("+")};
	unsigned int mod {0};
 	
	foreach (QString str, list) {
		if (str == "Ctrl"){
			
			mod += MOD_CONTROL;
			continue;
			
		} else if (str == "Alt") {
			
			mod += MOD_ALT;
			continue;

		} else if (str == "Shift") {
			
			mod += MOD_SHIFT; 
			continue;

		}
	}

	return mod;
}
unsigned int hotkey::hot_key(const QKeySequence& sequence)
{
	QStringList list = sequence.toString().split("+");
	char hotKey {0};
 
	foreach (QString str, list) {
		if (str != "Ctrl" && str != "Alt" && str != "Shift") {
			hotKey = str.at(0).unicode();
		}
	}

	return hotKey;
}
