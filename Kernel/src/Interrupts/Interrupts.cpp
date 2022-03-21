#include <Interrupts.h>
#include <PIC.hpp>
#include <APIC.h>

namespace Interrupts
{
	void RegisterInterrupt(void* handlerAddress, byte inter, IdtType interruptType)
	{
		IDTDescEntry* intDescEntry = (IDTDescEntry*)(GlobalIDTR.Offset + inter * sizeof(IDTDescEntry));
		intDescEntry->SetOffset((u64)handlerAddress);
		intDescEntry->TypeAttribs = interruptType;
		intDescEntry->Ignore = 0x00;
		intDescEntry->Selector = 0x08;
	}

	void LoadGIDT()
	{
		asm ("lidt %0" : : "m" (GlobalIDTR));
	}

	void PanicScreen()
	{
		gConsole.Clear(Color::DarkRed);
		gConsole.SetBackgroundColor(Color::DarkRed);
		gConsole.SetForegroundColor(Color(0xFFDDDDDD));
	}

	void hDivideByZeroFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("ERROR: DIVIDE BY ZERO FAULT!");
		halt;

		// bro just in case
		halt;
	}

	void hSingleStepFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Single Step");
		halt;
	}

	void hNonMaskableFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("NMI");
		halt;
	}

	void hBreakpointFault(InterruptFrame* frame)
	{
		//PanicScreen();
		gConsole.WriteLine("Breakpoint");
		halt;
	}

	void hOverflowTrap(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Overflow trap");
		halt;
	}

	void hBoundRangeFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Bound Range");
		halt;
	}

	void hInvalidOpcodeFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.Write("Invalid Opcode at address: ");
		gConsole.WriteLine(cstr::ToString(frame->ip, true));
		halt;
	}

	void hCoprocessorNAFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Coprocessor NA");
		halt;
	}

	void hDoubleFault(InterruptFrame* frame)
	{
		gConsole.Clear(Color::Red);
		gConsole.SetBackgroundColor(Color::Red);
		gConsole.SetForegroundColor(Color::White);
		gConsole.WriteLine("ERROR: DOUBLE FAULT!");
		halt;
	}

	void hCoprocessorSegmentOverrunFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Segment Overrun!");
		halt;
	}

	void hInvalidStateSegmentFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Invalid State Segment!");
		halt;
	}

	void hSegmentMissingFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Segment Missing!");
		halt;
	}

	void hStackFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Stack Exception!");
		halt;
	}

	void hGeneralProtectionFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("ERROR: GENERAL PROTECTION FAULT!");
		halt;
	}

	void hPageFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("ERROR: PAGE FAULT!");
		gConsole.Write("ATTEMPTED TO ACCESS ADDRESS: ");

		uint64 addr = 0;
		// cr2 contains the page fault linear address (PFLA)
		asm ("mov %0, %%cr2" : "=r" (addr) );

		gConsole.WriteLine(cstr::ToString(addr, true));

		halt;
	}

	void hCoprocessorFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("ERROR: COPROCESSOR FAULT!");
		halt;
	}

	void hAlignmentCheck(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Alignment Check");
		halt;
	}

	void hMachineCheck(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("Machine Check");
		halt;
	}

	void hSIMDFault(InterruptFrame* frame)
	{
		PanicScreen();
		gConsole.WriteLine("SIMD Exception");
		halt;
	}

	void hKeyboardInt(InterruptFrame* frame)
	{
		constexpr uint16 kbPort = 0x60;
		gConsole.Write("Key pressed ");
		
		// special ps2 magic
		byte scanCode = IO::inb(kbPort);

		// End of int
		if (APIC::InUse) APIC::EndOfInterrupt();
		else PIC::SendEIO(false);
	}

	void hStub(InterruptFrame* frame)
	{
		debug("Interrupt 0xFF called");
	}

}
