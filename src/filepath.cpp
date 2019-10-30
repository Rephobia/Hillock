#include <QFileInfo>

#include "filepath.hpp"

model::filepath::filepath(QString&& path)
	: m_path {std::move(path)}
	, m_dir  {QFileInfo {m_path}.path()}
	, m_name {QFileInfo {m_path}.fileName()}
{ ;}

const QString& model::filepath::path() const
{
	return m_path;
}

const QString& model::filepath::dir() const
{
	return m_dir;
}
const QString& model::filepath::name() const
{
	return m_name;
}
