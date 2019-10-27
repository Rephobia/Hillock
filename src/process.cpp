#include <string>

#include <windows.h>

#include "process.hpp"


namespace detail {
	
	std::string get_dir(const std::string& str);
	HANDLE shell_execute(const std::string& path);
	
	HANDLE create_job();
}

std::string detail::get_dir(const std::string& str)
{
	std::string::size_type found;

	found = str.find_last_of("/\\");

	return str.substr(0, found);
}

HANDLE detail::shell_execute(const std::string& path)
{
	SHELLEXECUTEINFO shell_info;

	::SecureZeroMemory(&shell_info, sizeof(shell_info));

	shell_info.cbSize = sizeof(shell_info);
	shell_info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_UNICODE;
	shell_info.nShow = SW_SHOWNORMAL;
	shell_info.lpFile = path.c_str();
	shell_info.lpDirectory = get_dir(path).c_str();

	::ShellExecuteEx(&shell_info);
	
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

void process::start_process(const std::string& path)
{	
	HANDLE process {detail::shell_execute(path)};
	
	if (process) {

		HANDLE job {detail::create_job()};
		
		bool success {::AssignProcessToJobObject(job, process)};
		
		if (not success) {
			::TerminateProcess(process, 0);
		}
	}
	
	::CloseHandle(process);
}
