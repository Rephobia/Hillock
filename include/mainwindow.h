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
	class keyedit;
}


class view::mainwindow : public QMainWindow
{
	Q_OBJECT
public:
	mainwindow(view::runners* runners);

	void set_quithotkey(const QKeySequence& quithotkey);
	
	~mainwindow();
	
	void dragEnterEvent(QDragEnterEvent* e);
	void dropEvent(QDropEvent* e);

	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
signals:
	void new_runner(const QString& filepath);
	void quit_edited(const QKeySequence& quithotkey);
protected:
	view::runners* m_runners;
	view::keyedit* m_quit_keyedit;
private:
	Ui::MainWindow* ui;
	
};


#endif // HILLOCK_MAINWINDOW_HPP
