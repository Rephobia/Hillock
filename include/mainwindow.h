#ifndef HILLOCK_MAINWINDOW_HPP
#define HILLOCK_MAINWINDOW_HPP


#include <QMainWindow>
#include <QVBoxLayout>

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
	Q_OBJECT
public:
	mainwindow(view::runners* runners,
	           QWidget* parent = nullptr);
	
	~mainwindow();
	
	void dragEnterEvent(QDragEnterEvent* e);
	void dropEvent(QDropEvent* e);
	
signals:
	void new_runner(const QString& filepath);
private:
	Ui::MainWindow* ui;
	view::runners* m_runners;
};


#endif // HILLOCK_MAINWINDOW_HPP
