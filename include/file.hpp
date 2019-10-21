#ifndef HILLOCK_FILE_HPP
#define HILLOCK_FILE_HPP


namespace model {
	class runner;
}

namespace model::dal {
	inline static const std::string FILE_NAME {"runners.txt"};
	
	std::vector<model::runner> read();
}


#endif // HILLOCK_FILE_HPP
