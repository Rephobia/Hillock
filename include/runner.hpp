#ifndef HILLOCK_RUNNER_HPP
#define HILLOCK_RUNNER_HPP


#include <list>

#include <QWidget>

#include "filepath.hpp"


class QVBoxLayout;

namespace view {
	class runners;
}


class view::runners : public QWidget
{
public:
	runners();
	void add(QString&& path);
	void run();
protected:
	void make_runner_widget(model::filepath& filepath);
	void remove_widget(QString&& path);
protected:
	QVBoxLayout* m_layout;
	std::list<model::filepath> m_runners;
};


#endif // HILLOCK_RUNNER_HPP
