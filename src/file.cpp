#include "file.hpp"


void model::dal::append(const QString& filepath)
{
	QFile file (model::dal::FILE_NAME);

	if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {

		model::dal::filestream filestream {&file};
		filestream << filepath << "\n";
		
		file.close();
	}
}

void model::dal::remove(const QString& filepath)
{
	QFile file {model::dal::FILE_NAME};
	
	if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
		
		QString buffer {};
		
		model::dal::filestream filestream {&file};
		
		while (not filestream.atEnd()) {
			
			QString line {filestream.readLine()};
			
			if (not line.contains(filepath))
				
				buffer.append(line + "\n");
		}
		
		file.resize(0);
		filestream << buffer;
		file.close();
	}
}
