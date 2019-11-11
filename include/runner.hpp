#ifndef HILLOCK_RUNNER_HPP
#define HILLOCK_RUNNER_HPP


#include <list>

#include <QWidget>

#include "filepath.hpp"


namespace model {
	class runners;
}


class model::runners
{
public:
	virtual model::filepath& add(QString&& filepath);
	
	void remove(const model::filepath& filepath);
	
	virtual ~runners() = default;
protected:
	std::list<model::filepath> m_runners;
};



class QVBoxLayout;

namespace view {
	class runners;
}


class view::runners : public QWidget
                    , public model::runners
{
	Q_OBJECT
public:
	runners();
	model::filepath& add(QString&& path) override;
	void run();
signals:
	void remove_runner(const QString& filepath);
protected:
	void make_runner_widget(model::filepath& filepath);
	void remove_widget(QString&& path);
protected:
	QVBoxLayout* m_layout;
};


#endif // HILLOCK_RUNNER_HPP
