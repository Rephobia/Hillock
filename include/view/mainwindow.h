#ifndef HILLOCK_VIEW_MAINWINDOW_HPP
#define HILLOCK_VIEW_MAINWINDOW_HPP


#include <QMainWindow>

namespace Ui
{
	class MainWindow;
}

namespace view
{
	class mainwindow;
	class runners_decorator;
	class keyedit;
}


class view::mainwindow : public QMainWindow
{
	Q_OBJECT
public:
	mainwindow(view::runners_decorator* runners);
	
	~mainwindow();
	
	void dragEnterEvent(QDragEnterEvent* e);
	void dropEvent(QDropEvent* e);

	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	
	void toggle_show();
	void changeEvent(QEvent* event);
	
	view::keyedit* quit_keyedit;
protected:
	view::runners_decorator* m_runners;
private:
	Ui::MainWindow* ui;
	
};

#endif // HILLOCK_VIEW_MAINWINDOW_HPP
