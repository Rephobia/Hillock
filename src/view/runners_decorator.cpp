#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

#include "view/runners_decorator.hpp"

using view::runners_decorator;

runners_decorator::runners_decorator()
	: m_layout {new QVBoxLayout {this}}
{
	m_layout->setAlignment(Qt::AlignTop);
	m_layout->setSpacing(0);
	m_layout->setMargin(0);
}


model::filepath& runners_decorator::add(QString&& path)
{
	emit new_runner(path);
	
	model::filepath& filepath {model::runners::add(std::move(path))};

	make_runner_widget(filepath);

	return filepath;
}


runners_decorator::runner::runner(model::filepath& filepath, QWidget* parent)
	: QWidget {parent}
	, remove  {new QPushButton {QStringLiteral("remove")}}
{
	remove->setFixedWidth(100);
	remove->setFixedHeight(20);

	auto layout {new QVBoxLayout {this}};
	
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->addWidget(this->make_item(filepath));
	layout->addWidget(this->make_separator());
}

QWidget* runners_decorator::runner::make_item(model::filepath& filepath)
{
	auto item {new QWidget {this}};
	auto layout {new QHBoxLayout {item}};
	
	auto filename {new QLabel {filepath.name()}};
	layout->addWidget(filename);
	layout->addWidget(remove);
				
	return item;
}

QWidget* runners_decorator::runner::make_separator()
{
	auto separator {new QFrame {this}};

	separator->setFrameShape(QFrame::HLine);
	separator->setFrameShadow(QFrame::Sunken);
	separator->setLineWidth(1);
	
	return separator;
}


void runners_decorator::make_runner_widget(model::filepath& filepath)
{
	auto runner {new runners_decorator::runner {filepath, this}};
	
	QObject::connect(runner->remove, &QPushButton::clicked,
	                 [this, runner, &filepath]()
	                 {
		                 emit remove_runner(filepath.path());

		                 runner->hide();
		                 runner->deleteLater();
		                 
		                 model::runners::remove(filepath);
	                 });
	
	m_layout->addWidget(runner);
}
