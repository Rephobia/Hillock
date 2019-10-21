#include <iostream>

#include <QString>
#include <QLabel>

#include "runner.hpp"

using model::runner;

runner::runner(QString&& path)
	: m_path {std::move(path)}
{ ;}


void runner::start()
{
	std::cout << "Start: " << m_path.toStdString() << std::endl;
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
	: m_layout {new QVBoxLayout {}}
{
	QWidget::setLayout(m_layout);
}

void runners::add(model::runner&& runner)
{
	m_layout->addWidget(new QLabel {runner.name()});
	m_runners.push_back(std::move(runner));
}
