#include <windows.h>
#include <QMessageBox>
#include <QApplication>

#include "hotkey.hpp"


bool hotkey::check_button(void* message)
{
	auto msg {static_cast<MSG*>(message)};
	
	if (msg->message == WM_HOTKEY) {
		QApplication::quit();
		return true;
	}

	return false;
}


namespace hotkey::detail {
	unsigned int mod_key(const QKeySequence& sequence);
	unsigned int hot_key(const QKeySequence& sequence);	
}

unsigned int hotkey::detail::mod_key(const QKeySequence& sequence)
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

unsigned int hotkey::detail::hot_key(const QKeySequence& sequence)
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



void hotkey::quit::register_button(QWidget* mainwindow, const QKeySequence& sequence)
{
	auto winid {mainwindow->winId()};
	
	int hotkeyid {100};
	
	::UnregisterHotKey(HWND(winid), hotkeyid);
	
	if (not ::RegisterHotKey(HWND(winid), hotkeyid,
	                         detail::mod_key(sequence),
	                         detail::hot_key(sequence))) {

		QMessageBox::warning(mainwindow, "Warning", "Can't register hotkey error: "
		                     + QString::number(GetLastError()));

	}

	emit bell::instance().reg_hotkey(sequence);
}
