#ifndef HILLOCK_MAINWINDOW_HPP
#define HILLOCK_MAINWINDOW_HPP


#include <QMainWindow>


namespace model
{
	class runner;
}

namespace Ui
{
	class MainWindow;
}

namespace view
{
	class mainwindow;
	class runners;
}


class view::mainwindow : public QMainWindow
{                          
public:
	mainwindow(view::runners* runners,
	           QWidget* parent = nullptr);
	
	~mainwindow();
	
	void dragEnterEvent(QDragEnterEvent* e);
	void dropEvent(QDropEvent* e);
private:
	Ui::MainWindow* ui;
};


#endif // HILLOCK_MAINWINDOW_HPP
