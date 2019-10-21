#include <vector>
#include <fstream>

#include <QString>

#include "file.hpp"
#include "runner.hpp"


std::vector<model::runner> model::dal::read()
{
	std::vector<model::runner> runners {};
 
	std::ifstream file {model::dal::FILE_NAME};
	
	if (file.is_open()) {
		
		std::string line {};
		
		while (std::getline(file, line)) {

			QString string {QString::fromUtf8(line.c_str())};
			runners.push_back(model::runner {std::move(string)});
			
		}
		
	} else {
		std::ofstream create_file {model::dal::FILE_NAME};
		create_file.close();
	}
	
	file.close();
	
	return runners;
}

