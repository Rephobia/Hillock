#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QKeySequence>

#include "mapper.hpp"
#include "runner.hpp"
#include "hotkey.hpp"

using data::mapper;

void mapper::read(model::runners* runners, hotkey::quit& quithotkey)
{
	QFile file {mapper::FILE_NAME};

	if (file.open(QIODevice::ReadOnly)) {
				
		QJsonParseError parse_error;
		QJsonDocument document {QJsonDocument::fromJson(file.readAll(), &parse_error)};
		
		if (parse_error.error == QJsonParseError::NoError) {
				
			if (document.isObject()) {
					
				QJsonObject jobject {document.object()};
		
				for (QJsonValueRef e : jobject[mapper::RUNNERS].toArray()) {
					runners->add(e.toString());
				}

				QJsonObject::iterator quit {jobject.find(mapper::QUIT)};

				if (quit != jobject.end()) {
					quithotkey.register_key(quit.value().toString());
				}

				m_jobject = std::move(jobject);
			}
		}
	}
}

void mapper::append_runner(const QString& filepath)
{
	QJsonObject new_jobject {m_jobject};

	QJsonObject::iterator runners_it {new_jobject.find(mapper::RUNNERS)};
	
	if (runners_it != new_jobject.end()) {

		// Be careful, you must not use uniform init for QJsonArray {QJsonValue.toArray()}.
		// Use assign QJsonarray = QJsonValue::toArray();
		// this is GCC bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92400
		// Qt bugtracker https://bit.ly/2O0YQmN
		
		QJsonArray runners = runners_it->toArray();

		runners.append(filepath);

		*runners_it = runners;
	}
	else {

		new_jobject.insert(mapper::RUNNERS, QJsonArray {filepath});

	}

	mapper::write(m_jobject, new_jobject);


}

void mapper::remove_runner(const QString& filepath)
{
	QJsonObject new_jobject {m_jobject};

	QJsonObject::iterator runners_it {new_jobject.find(mapper::RUNNERS)};

	if (runners_it != new_jobject.end()) {

		// Be careful, you must not use uniform init for QJsonArray {QJsonValue.toArray()}.
		// Use assign QJsonarray = QJsonValue::toArray();
		// this is GCC bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92400
		// Qt bugtracker https://bit.ly/2O0YQmN
		
		QJsonArray runners = runners_it->toArray();
		
		for (QJsonArray::size_type i = runners.size(); i--;) {
		
			if (runners[i] == filepath) {

				runners.removeAt(i);
				*runners_it = runners;
				break;
			}
		}
	}
	
	write(m_jobject, new_jobject);
}

void mapper::write(QJsonObject& old_object, const QJsonObject& new_object)
{
	QFile file {mapper::FILE_NAME};

	if (file.open(QIODevice::WriteOnly)) {
		
		file.resize(0);
		file.write(QJsonDocument(new_object).toJson(QJsonDocument::Indented));
		file.close();
		
		old_object = new_object;
		
	}
}
void mapper::set_quithotkey(const QKeySequence& quithotkey)
{
	QJsonObject new_jobject {m_jobject};	
		
	QJsonObject::iterator quit {new_jobject.find(mapper::QUIT)};

	if (quit != new_jobject.end()) {
		*quit = quithotkey.toString();
	} else {
		new_jobject.insert(mapper::QUIT, QJsonValue {quithotkey.toString()});
	}
	
	write(m_jobject, new_jobject);
	
}
