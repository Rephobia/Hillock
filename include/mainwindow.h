#ifndef HILLOCK_MAINWINDOW_HPP
#define HILLOCK_MAINWINDOW_HPP


#include <QMainWindow>

namespace Ui
{
	class MainWindow;
}

namespace view
{
	class mainwindow;
	class runners;
	class hotkey;
}


class view::mainwindow : public QMainWindow
{
	Q_OBJECT
public:
	mainwindow(view::runners* runners,
	           QWidget* parent = nullptr);
	
	~mainwindow();
	
	void dragEnterEvent(QDragEnterEvent* e);
	void dropEvent(QDropEvent* e);

	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	void parse_key();
signals:
	void new_runner(const QString& filepath);
private:
	Ui::MainWindow* ui;
	view::hotkey* m_hotkey;
	view::runners* m_runners;
};


#endif // HILLOCK_MAINWINDOW_HPP
