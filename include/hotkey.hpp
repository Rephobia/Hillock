#ifndef HILLOCK_HOTKEY_HPP
#define HILLOCK_HOTKEY_HPP


class QWidget;
class QKeySequence;


namespace hotkey {
	
	class quit;
	
	bool check_button(void* message);
}

class hotkey::quit : public QObject
{
	Q_OBJECT
public:
	quit(QWidget* mainwindow);
	const QKeySequence& sequence() const;
	void register_key(const QKeySequence& sequence);
signals:
	void registered(const QKeySequence& sequence);
protected:
	QKeySequence m_sequence;
	QWidget* m_mainwindow;
	int m_keyid {100};
};

#endif // HILLOCK_HOTKEY_HPP
