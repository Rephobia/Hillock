#ifndef HILLOCK_RUNNER_HPP
#define HILLOCK_RUNNER_HPP


namespace model
{
	class runner;	
}


class model::runner
{
public:
	explicit runner(QString&& path);
	
	void start();
	
	QString name();
	void change_path(QString&& path);
protected:
	QString m_path;
};


#endif // HILLOCK_RUNNER_HPP
