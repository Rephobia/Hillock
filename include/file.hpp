#ifndef HILLOCK_FILE_HPP
#define HILLOCK_FILE_HPP


#include <QString>
#include <QFile>
#include <QTextStream>

namespace model::dal {
	
	inline static const QString FILE_NAME {"runners.txt"};


	class filestream : public QTextStream
	{
	public:
		filestream(QFile *file)
			: QTextStream {file}
		{
			setCodec("UTF-8");			
		}
	};

	
	template<typename T>
	void read(T& storage)
	{
		QFile file {model::dal::FILE_NAME};

		if (file.open(QIODevice::ReadOnly)) {

			model::dal::filestream filestream {&file};

			while (not filestream.atEnd()) {
			
				QString line {filestream.readLine()};
			
				storage->add(std::move(line));
						
			}
		
			file.close();
		}
	}
	
	void append(const QString& filepath);
	void remove(const QString& filepath);
}


#endif // HILLOCK_FILE_HPP
