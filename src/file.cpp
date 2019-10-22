#include "file.hpp"

void model::dal::append(const QString& filepath)
{
	std::ofstream outfile;

	outfile.open(model::dal::FILE_NAME, std::ios_base::app);
	outfile << filepath.toStdString() << std::endl; 
}
