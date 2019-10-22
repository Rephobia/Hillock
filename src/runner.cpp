#include <QString>
#include <QLabel>
#include <QProcess>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

#include "runner.hpp"
#include "file.hpp"


using model::runner;

runner::runner(QString&& path)
	: m_path {std::move(path)}
{ ;}


void runner::start(QObject* parent)
{
	if (m_path.contains(".ahk")) {
		QDesktopServices::openUrl(QUrl::fromLocalFile(m_path));
	}
	else {
		auto process {new QProcess {parent}};
		process->start(m_path);	
	}
}

const QString& runner::name() const
{
	return m_path;
}

void runner::change_path(QString&& path)
{
	m_path = std::move(path);
}


using view::runners;

runners::runners()
	: m_layout {new QVBoxLayout {this}}
{ ;}


void runners::add(QString&& path)
{	
	decltype(auto) runner {m_runners.emplace_back(model::runner {std::move(path)})};

	make_runner_widget(runner);
}

void runners::make_runner_widget(model::runner& runner)
{
	auto widget {new QWidget {}};
	widget->setObjectName(runner.name());
	
	auto runner_lay {new QHBoxLayout {widget}};

	runner_lay->addWidget(new QLabel {runner.name()});

	auto remove {new QPushButton {"remove"}};
	
	QObject::connect(remove, &QPushButton::clicked,
	                 [this, &runner]()
	                 {
		                 model::dal::remove(runner.name().toStdString());

		                 auto lambda {[&runner](const model::runner& obj)
		                              {
			                              return runner.name() == obj.name();
		                              }};
		                 
		                 auto it {std::find_if(m_runners.begin(), m_runners.end(), lambda)};

		                 auto widget {this->findChild<QWidget*>(runner.name())};
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
		e.start(this);
	}
}
