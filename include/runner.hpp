#ifndef HILLOCK_RUNNER_HPP
#define HILLOCK_RUNNER_HPP


#include <list>

#include <QVBoxLayout>
#include <QWidget>


namespace model {
	class runner;	
}

namespace view {
	class runners;
}


class model::runner
{
public:
	explicit runner(QString&& path);
	
	void start(QObject* parent);
	
	const QString& name() const;
	void change_path(QString&& path);
protected:
	QString m_path;
};


class view::runners : public QWidget
{
public:
	runners();
	void add(QString&& path);
	void run();
protected:
	void make_runner_widget(model::runner& runner);
	void remove_widget(QString&& path);
protected:
	QVBoxLayout* m_layout;
	std::list<model::runner> m_runners;
};


#endif // HILLOCK_RUNNER_HPP
