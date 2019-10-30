#ifndef HILLOCK_PATH_HPP
#define HILLOCK_PATH_HPP


#include <QString>


namespace model {
	class filepath;
}


class model::filepath
{
public:
	explicit filepath(QString&& path);

	const QString& path() const;
	const QString& dir() const;
	const QString& name() const;
protected:
	QString m_path;
	QString m_dir;
	QString m_name;
};


#endif // HILLOCK_PATH_HPP
