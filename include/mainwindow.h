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
}


class view::mainwindow : public QMainWindow
{                          
public:
	mainwindow(std::vector<model::runner> runners,
	           QWidget* parent = nullptr);
	
	~mainwindow();
	
	void dragEnterEvent(QDragEnterEvent* e);
	void dropEvent(QDropEvent* e);
private:
	Ui::MainWindow* ui;
};


#endif // HILLOCK_MAINWINDOW_HPP
