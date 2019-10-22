#ifndef HILLOCK_FILE_HPP
#define HILLOCK_FILE_HPP


#include <fstream>

#include <QString>

namespace model::dal {
	
	inline static const std::string FILE_NAME {"runners.txt"};

	template<typename T>
	void read(T& storage)
	{
		std::ifstream file {model::dal::FILE_NAME};
	
		if (file.is_open()) {
		
			std::string line {};
		
			while (std::getline(file, line)) {

				storage->add(QString::fromUtf8(line.c_str()));
			
			}
		} else {
			std::ofstream create_file {model::dal::FILE_NAME};
			create_file.close();
		}
	
		file.close();
	}
	
	void append(const QString& filepath);
}


#endif // HILLOCK_FILE_HPP
