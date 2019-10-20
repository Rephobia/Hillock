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
}

class view::mainwindow : public QMainWindow
{
	Q_OBJECT
public:
	mainwindow(QWidget* parent = nullptr);
	~mainwindow();
	
	void dragEnterEvent(QDragEnterEvent* e);
	void dropEvent(QDropEvent* e);
private:
	Ui::MainWindow* ui;
};


#endif // HILLOCK_MAINWINDOW_HPP
