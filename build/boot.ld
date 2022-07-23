OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
	imem (wxa!ri)	: ORIGIN = 0x80000000, LENGTH = 20K
	dmem 		: ORIGIN = 0x80005000, LENGTH = 100K
}

SECTIONS
{
	.text : {
		PROVIDE(_text_start = .);
		*(.text .text.*)
		PROVIDE(_text_end = .);
	} > imem

	.rodata : {
		PROVIDE(_rodata_start = .);
		*(.rodata .rodata.*)
		PROVIDE(_rodata_end = .);
	} > dmem

	.data : {
		PROVIDE(_data_start = .);
		*(.data .data.*)
		PROVIDE(_data_end = .);
	} > dmem

	.bss : {
		PROVIDE(_bss_start = .);
		*(.sbss .sbss.*)
		*(.bss .bss.*)
		*(COMMON)
		PROVIDE(_bss_end = .);
	} > dmem

	PROVIDE(_mem_start = ORIGIN(imem));
	PROVIDE(_mem_end = ORIGIN(imem) + LENGTH(imem) + LENGTH(dmem));
	PROVIDE(_heap_start = _bss_end);
	PROVIDE(_heap_end = _mem_end);
	PROVIDE(_heap_size = _heap_end - _heap_start);
}
