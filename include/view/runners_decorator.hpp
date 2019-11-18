#ifndef HILLOCK_VIEW_RUNNERS_DECORATOR_HPP
#define HILLOCK_VIEW_RUNNERS_DECORATOR_HPP


#include <QWidget>

#include "runners.hpp"


class QVBoxLayout;
class QPushButton;

namespace view {
	class runners_decorator;
}


class view::runners_decorator : public QWidget
                              , public model::runners
{
	Q_OBJECT
public:
	runners_decorator();
	model::filepath& add(QString&& path) override;
signals:
	void new_runner(const QString& filepath);
	void remove_runner(const QString& filepath);
protected:
	class runner;
	void make_runner_widget(model::filepath& filepath);
	void remove_widget(QString&& path);
protected:
	QVBoxLayout* m_layout;
};


class view::runners_decorator::runner : public QWidget
{
public:
	runner(model::filepath& filepath, QWidget* parent);
	
	QPushButton* remove;
private:
	QWidget* make_item(model::filepath& filepath);
	QWidget* make_separator();
};

#endif // HILLOCK_VIEW_RUNNERS_DECORATOR_HPP
