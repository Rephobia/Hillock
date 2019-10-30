#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

#include "filepath.hpp"
#include "file.hpp"

#include "process.hpp"
#include "runner.hpp"

using view::runners;

runners::runners()
	: m_layout {new QVBoxLayout {this}}
{ ;}


void runners::add(QString&& path)
{	
	decltype(auto) filepath {m_runners.emplace_back(model::filepath {std::move(path)})};

	make_runner_widget(filepath);
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
		                 model::dal::remove(filepath.path());

		                 auto lambda {[&filepath](const model::filepath& obj)
		                              {
			                              return filepath.path() == obj.path();
		                              }};
		                 
		                 auto it {std::find_if(m_runners.begin(), m_runners.end(), lambda)};

		                 auto widget {this->findChild<QWidget*>(filepath.path())};
		                 widget->hide();
		                 widget->deleteLater();
		                 m_runners.erase(it);
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
