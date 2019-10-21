#include <iostream>

#include <QString>

#include "runner.hpp"

using model::runner;

runner::runner(QString&& path)
	: m_path {std::move(path)}
{ ;}


void runner::start()
{
	std::cout << "Start: " << m_path.toStdString() << std::endl;
}

QString runner::name()
{
	return m_path;
}

void runner::change_path(QString&& path)
{
	m_path = std::move(path);
}
