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

	void set_quithotkey(const QKeySequence& quithotkey);
	
	~mainwindow();
	
	void dragEnterEvent(QDragEnterEvent* e);
	void dropEvent(QDropEvent* e);

	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	
	void toggle_show();
	void changeEvent(QEvent* event);
signals:
	void new_runner(const QString& filepath);
	void quit_edited(const QKeySequence& quithotkey);
protected:
	view::runners_decorator* m_runners;
private:
	view::keyedit* m_quit_keyedit;
	Ui::MainWindow* ui;
	
};

#endif // HILLOCK_VIEW_MAINWINDOW_HPP
