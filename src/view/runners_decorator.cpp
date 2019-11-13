#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

#include "view/runners_decorator.hpp"

using view::runners_decorator;

runners_decorator::runners_decorator()
	: m_layout {new QVBoxLayout {this}}
{ ;}


model::filepath& runners_decorator::add(QString&& path)
{
	model::filepath& filepath {model::runners::add(std::move(path))};

	make_runner_widget(filepath);

	return filepath;
}

void runners_decorator::make_runner_widget(model::filepath& filepath)
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
