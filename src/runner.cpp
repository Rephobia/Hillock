#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

#include "filepath.hpp"

#include "process.hpp"
#include "runner.hpp"


model::filepath& model::runners::add(QString&& path)
{
	model::filepath filepath {std::move(path)};
	
	return m_runners.emplace_back(filepath);	
}

void model::runners::remove(const model::filepath& filepath)
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

using view::runners;

runners::runners()
	: m_layout {new QVBoxLayout {this}}
{ ;}


model::filepath& runners::add(QString&& path)
{
	model::filepath& filepath {model::runners::add(std::move(path))};

	make_runner_widget(filepath);

	return filepath;
}

void runners::make_runner_widget(model::filepath& filepath)
{
	auto widget {new QWidget {}};
	widget->setObjectName(filepath.path());
	
	auto runner_lay {new QHBoxLayout {widget}};

	runner_lay->addWidget(new QLabel {filepath.name()});

	auto remove {new QPushButton {"remove"}};
	
	QObject::connect(remove, &QPushButton::clicked,
	                 [this, &filepath]()
	                 {
		                 emit remove_runner(filepath.path());

		                 auto widget {this->findChild<QWidget*>(filepath.path())};
		                 widget->hide();
		                 widget->deleteLater();
		                 
		                 model::runners::remove(filepath);

	                 });
	
	runner_lay->addWidget(remove);

	m_layout->addWidget(widget);
}

void runners::run()
{
	for (auto& e : m_runners) {
		process::start_process(e);
	}
}
