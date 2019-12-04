/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

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
#include <windows.h>

#include "filepath.hpp"
#include "process.hpp"


namespace detail {
	
	HANDLE shell_execute(const model::filepath& filepath);
	
	HANDLE create_job();
	
}


HANDLE detail::shell_execute(const model::filepath& filepath)
{
	SHELLEXECUTEINFOW shell_info;

	::SecureZeroMemory(&shell_info, sizeof(shell_info));

	shell_info.cbSize = sizeof(shell_info);
	shell_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	shell_info.nShow = SW_SHOWNORMAL;

	shell_info.lpFile = reinterpret_cast<LPCWSTR>(filepath.path().utf16());
	shell_info.lpDirectory = reinterpret_cast<LPCWSTR>(filepath.dir().utf16());
	
	::ShellExecuteExW(&shell_info);
	
	return shell_info.hProcess;
}

HANDLE detail::create_job()
{
	HANDLE job {::CreateJobObject(nullptr, nullptr)};
	
	JOBOBJECT_EXTENDED_LIMIT_INFORMATION info {};
	
	info.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	
	::SetInformationJobObject(job, JobObjectExtendedLimitInformation,
	                          &info, sizeof(info));
	return job;
}

void process::start_process(const model::filepath& filepath)
{	
	HANDLE process {detail::shell_execute(filepath)};
	
	if (process) {

		HANDLE job {detail::create_job()};
		
		bool success {::AssignProcessToJobObject(job, process)};
		
		if (not success) {
			::TerminateProcess(process, 0);
		}
	}
	
	::CloseHandle(process);
}
