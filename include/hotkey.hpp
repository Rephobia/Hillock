#ifndef HILLOCK_HOTKEY_HPP
#define HILLOCK_HOTKEY_HPP


class QWidget;
class QKeySequence;


namespace hotkey {
	bool check_button(void* message);
}

namespace hotkey::quit {
	void register_button(QWidget* mainwindow, const QKeySequence& sequence);

	class bell : public QObject
	{
		Q_OBJECT
	public:
		bell(const bell&) = delete;
		bell& operator= (const bell&) = delete;
		
		static bell& instance()
		{
			static bell b {};
			return b;
		}
	signals:
		void reg_hotkey(const QKeySequence& sequence);
	private:
		bell() = default;
		~bell() = default;
	};
}

#endif // HILLOCK_HOTKEY_HPP
