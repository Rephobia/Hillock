#ifndef HILLOCK_RUNNER_HPP
#define HILLOCK_RUNNER_HPP


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
	void add(model::runner&& runner);
	void run();
protected:
	QVBoxLayout* m_layout;
	std::vector<model::runner> m_runners;
};


#endif // HILLOCK_RUNNER_HPP
