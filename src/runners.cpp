/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov <doomerroman@gmail.com>

 * This file is part of Memedar (flashcard system)
 * Memedar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
