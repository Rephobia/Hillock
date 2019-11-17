#ifndef HILLOCK_MAPPER_HPP
#define HILLOCK_MAPPER_HPP


#include <QString>
#include <QJsonObject>

namespace model {
	class runners;
}

namespace data {
	class mapper;
}

namespace hotkey {
	class quit;
}


class data::mapper : public QObject
{
	Q_OBJECT
public:
	mapper(QWidget* mainwindow);
	
	void read(model::runners* runners, hotkey::quit& quithotkey);
	void append_runner(const QString& filepath);
	void set_quithotkey(const QKeySequence& quithotkey);
	
	void remove_runner(const QString& filepath);
protected:
	void read(const QJsonDocument& document, model::runners* runners, hotkey::quit& quithotkey);
	// assign new object to old object if new object was written to json file
	void write(QJsonObject& old_object, QJsonObject&& new_object);
	
	QJsonObject m_jobject;
	QWidget* m_mainwindow;
protected:
	inline static const QString FILE_NAME {QStringLiteral("runners.json")};
	inline static const QString RUNNERS {QStringLiteral("runners")};
	inline static const QString QUIT {QStringLiteral("QUIT")};
};


#endif // HILLOCK_MAPPER_HPP
