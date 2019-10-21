#ifndef HILLOCK_FILE_HPP
#define HILLOCK_FILE_HPP


namespace model {
	class runner;
}

namespace view {
	class runners;
}

namespace model::dal {
	inline static const std::string FILE_NAME {"runners.txt"};
	
	view::runners* read();
	void append(const QString& filepath);
}


#endif // HILLOCK_FILE_HPP
