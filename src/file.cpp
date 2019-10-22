#include "file.hpp"

void model::dal::append(const QString& filepath)
{
	std::ofstream file;

	file.open(model::dal::FILE_NAME, std::ios_base::app);
	file << filepath.toStdString() << std::endl;
	
	file.close();
}

void model::dal::remove(const std::string& filepath)
{
	std::string temp_file {"temp_" + model::dal::FILE_NAME};
	
	std::ifstream file {model::dal::FILE_NAME};
	std::ofstream temp {temp_file};

	if (file.is_open() and temp.is_open()) {
		std::string curr_filepath {};
		
		while (std::getline(file, curr_filepath)) {
			
			if (curr_filepath != filepath) {
				temp << curr_filepath << std::endl;
			}
		}
	}
	temp.close();
	file.close();
	
	::remove(model::dal::FILE_NAME.c_str());
	::rename(temp_file.c_str(), model::dal::FILE_NAME.c_str());
}
