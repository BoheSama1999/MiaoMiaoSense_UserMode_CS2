#include <stdio.h>
#include <cstdint>
#include <string>
#include <Windows.h>
#include <tlhelp32.h>
#include <thread>

#include "MiaoMiaoSense.hpp"
#include "MemCat.hpp"
#include "Driver.hpp"
#include "Utils.hpp"
#include "Features.hpp"
#include "SDK.hpp"

bool bhop = 1; //for test

HANDLE driverhandle = 0;
uintptr_t client = 0;
	//  Cheat Sense idea for develop
	// MiaoMiaoSense -> if Driver exist
	// |=> exist -> next
	// |=> not exist -> load driver
	// -> program exist -> Start init Progress -> Get Driver(baseaddress and client.dll address)  
	// -> Read Setting -> Init Features -> Memory(Enable Features) -> Waiting for setting changes -> Memory(enable or diable Features)
	// |=> Game closed -> cheat waiting game start
	// |=> Cheat closed

//const HANDLE driverhandle;
//uintptr_t client;
	
int main(int argc, char* argv[]) // main function , args ->
{
	// For args


	//
	HANDLE* pd = &driverhandle;
	uintptr_t* pc = &client;
	
								
	const DWORD cs2_pid = get_process_id(L"cs2.exe"); // get pid
	Assert(cs2_pid != 0, "Unable to find running cs2.exe process", "Obtained cs2.exe process");
					
	*pd = CreateFile(L"\\\\.\\MiaoMiaoSense", GENERIC_READ, 0, nullptr, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, nullptr); // init driver
	Assert(*pd != INVALID_HANDLE_VALUE, "Unable to create driver", "Created driver");

	Assert(driver::attach_to_process(*pd , cs2_pid), "Unable to attach driver to process", "Attached driver to cs2.exe");
								
	*pc = get_module_base(cs2_pid, L"client.dll"); // get client.dll base address
	Assert(*pc != 0, "Client.dll not found", "Client.dll successfully found");

	

	while (true) {
		if (GetAsyncKeyState(VK_END)) break; // exit cheat with "end" key
			Features::bunny_hop();
			Features::RCS();
			//std::thread BHop(Features::RCS);
			//std::thread RCS(Features::RCS);
	}

	CloseHandle(driverhandle);
	std::cin.get();
	return 0;



}