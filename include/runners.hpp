#ifndef HILLOCK_MODEL_RUNNERS_HPP
#define HILLOCK_MODEL_RUNNERS_HPP


#include <list>

#include "filepath.hpp"


namespace model {
	class runners;
}


class model::runners
{
public:
	virtual model::filepath& add(QString&& filepath);
	
	void remove(const model::filepath& filepath);
	void run();
	virtual ~runners() = default;
private:
	std::list<model::filepath> m_runners;
};


#endif // HILLOCK_MODEL_RUNNERS_HPP
