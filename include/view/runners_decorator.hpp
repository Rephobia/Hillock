#ifndef HILLOCK_VIEW_RUNNERS_DECORATOR_HPP
#define HILLOCK_VIEW_RUNNERS_DECORATOR_HPP


#include <QWidget>

#include "runners.hpp"


class QVBoxLayout;

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
	void make_runner_widget(model::filepath& filepath);
	void remove_widget(QString&& path);
protected:
	QVBoxLayout* m_layout;
};


#endif // HILLOCK_VIEW_RUNNERS_DECORATOR_HPP
