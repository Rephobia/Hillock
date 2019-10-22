#include <vector>
#include <fstream>

#include <QString>

#include "file.hpp"
#include "runner.hpp"


view::runners* model::dal::read()
{
	auto runners {new view::runners {}};
 
	std::ifstream file {model::dal::FILE_NAME};
	
	if (file.is_open()) {
		
		std::string line {};
		
		while (std::getline(file, line)) {

			runners->add(QString::fromUtf8(line.c_str()));
			
		}
	} else {
		std::ofstream create_file {model::dal::FILE_NAME};
		create_file.close();
	}
	
	file.close();
	
	return runners;
}

void model::dal::append(const QString& filepath)
{
	std::ofstream outfile;

	outfile.open(model::dal::FILE_NAME, std::ios_base::app);
	outfile << filepath.toStdString() << std::endl; 
}
