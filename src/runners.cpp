#include "filepath.hpp"

#include "process.hpp"
#include "runners.hpp"


using model::runners;

model::filepath& runners::add(QString&& path)
{
	model::filepath filepath {std::move(path)};
	
	return m_runners.emplace_back(filepath);	
}

void runners::remove(const model::filepath& filepath)
{
	auto lambda {[&filepath](const model::filepath& obj)
	             {
		             return filepath.path() == obj.path();
	             }};
	
	auto it {std::find_if(m_runners.begin(), m_runners.end(), lambda)};

	if (it != m_runners.end()) {
		m_runners.erase(it);
	}
}

void runners::run()
{
	for (auto& e : m_runners) {
		process::start_process(e);
	}
}
