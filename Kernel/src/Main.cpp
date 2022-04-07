#include <KernelUtils.h>

namespace Kernel
{
	inline void ClearBss(BootInfo& bootInfo)
	{
		vptr bssStart = &_BssDataStart;
		vptr bssEnd = &_BssDataEnd;
		u64 bssSize = u64(bssEnd) - u64(bssStart);
		memset64(bssStart, 0x00, bssSize);
	}
	
	void oneSecond()
	{
		static int sec = 0;
		sec++;
		debug("Sec: %0", sec);
	}

	global void KernelStart(BootInfo bootInfo)
	{
		// Clear uninitialized data (just to be sure)
		ClearBss(bootInfo);

		// Create console
		gConsole = PrimitiveConsole(bootInfo.Framebuffer, bootInfo.font);
		gConsole.Clear();

		#ifndef NO_ANIME
		// Show loading image
		ShowLoadingImage(bootInfo);
		#endif

		// Initialize Hardware
		Kernel::InitializeKernel(bootInfo);

		gConsole.WriteLine(string(OSName) + " Initialized!", Color::Green);
		Memory::PrintLeaks();

		PIT::SleepMS(1000);

		while (true)
		{
			Audio::PlayTrack(Audio::NotTetris);
		}

		while (true) hlt;
	}
}