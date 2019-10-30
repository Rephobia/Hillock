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
