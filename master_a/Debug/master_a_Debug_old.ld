/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-13
 * (c) NXP Semiconductors 2013-2017
 * Generated linker script file for LPC4337
 * Created from generic_c.ld (7.9.2 ())
 * By LPCXpresso v7.9.2 [Build 493] [2015-09-14]  on Fri Sep 22 10:41:20 ART 2017
 */


INCLUDE "master_a_Debug_library.ld"
INCLUDE "master_a_Debug_memory.ld"

ENTRY(ResetISR)

SECTIONS
{
    
    /* _core_m0app text section */
    .text.core_m0app_text : SUBALIGN(4)
    {
       FILL(0xff)
       __core_m0app_START__ = .; /* start of slave image */
       KEEP(*(.core_m0app))
    } > MFlashB512
    
    /* _core_m0app extab and exidx sections */
    .text.core_m0app_ARM_extab . : SUBALIGN(4)
    {
       FILL(0xff)
    	KEEP(*(.core_m0app.ARM.extab))
    } 
    
    .text.core_m0app_ARM_exidx . : SUBALIGN(4)
    {
       FILL(0xff)
    	KEEP(*(.core_m0app.ARM.exidx))
    } 
    
    /* _core_m0app data section */
    .text.core_m0app_data . : SUBALIGN(4)
    {
       FILL(0xff)
       KEEP(*(.core_m0app.data_*)) KEEP(*(.core_m0app.data))
       __core_m0app_END__ = .; /* end of slave image */
    
       /* perform some simple sanity checks */
       ASSERT(!(__core_m0app_START__ == __core_m0app_END__), "No slave code for _core_m0app");
       ASSERT( (ABSOLUTE(__core_m0app_START__) == __vectors_start___core_m0app), "M0APP execute address differs from address provided in source image");
    } 
    
    .text_Flash2 : ALIGN(4)
    {
       FILL(0xff)
    	*(.text_Flash2*) /* for compatibility with previous releases */
    	*(.text_MFlashB512*) /* for compatibility with previous releases */
    	*(.text.$Flash2*)
    	*(.text.$MFlashB512*)
    	*(.rodata.$Flash2*)
    	*(.rodata.$MFlashB512*)
    } > MFlashB512

    /* MAIN TEXT SECTION */    
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */
        

        *(.after_vectors*)
        
        /* Code Read Protect data */
        . = 0x000002FC ;
        PROVIDE(__CRP_WORD_START__ = .) ;
        KEEP(*(.crp))
        PROVIDE(__CRP_WORD_END__ = .) ;
        ASSERT(!(__CRP_WORD_START__ == __CRP_WORD_END__), "Linker CRP Enabled, but no CRP_WORD provided within application");
        /* End of Code Read Protect */
        
    } >MFlashA512
    
    .text : ALIGN(4)    
    {
         *(.text*)
        *(.rodata .rodata.* .constdata .constdata.*)
        . = ALIGN(4);
        
    } > MFlashA512

    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this. 
     */
    .ARM.extab : ALIGN(4)
    {
    	*(.ARM.extab* .gnu.linkonce.armextab.*)
    } > MFlashA512
    __exidx_start = .;
    
    .ARM.exidx : ALIGN(4)
    {
    	*(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > MFlashA512
    __exidx_end = .;
    
    _etext = .;

    
    /* DATA section for RamLoc40 */
    
    .data_RAM2 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM2 = .) ;
       *(.ramfunc.$RAM2)
       *(.ramfunc.$RamLoc40)
    	*(.data.$RAM2*)
    	*(.data.$RamLoc40*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM2 = .) ;
    } > RamLoc40 AT>MFlashA512
    
    /* MAIN DATA SECTION */
    

    .uninit_RESERVED : ALIGN(4)
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > RamLoc32

	
	/* Main DATA section (RamLoc32) */
	.data : ALIGN(4)
	{
	   FILL(0xff)
	   _data = . ;
	   *(vtable)
	   *(.ramfunc*)
	   *(.data*)
	   . = ALIGN(4) ;
	   _edata = . ;
	} > RamLoc32 AT>MFlashA512

    /* BSS section for RamLoc40 */
    .bss_RAM2 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
    	*(.bss.$RAM2*)
    	*(.bss.$RamLoc40*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
    } > RamLoc40

    /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
    } > RamLoc32
        
    /* NOINIT section for RamLoc40 */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM2*)
    	*(.noinit.$RamLoc40*)
       . = ALIGN(4) ;
    } > RamLoc40 
    
    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        *(.noinit*) 
         . = ALIGN(4) ;
        _end_noinit = .;
    } > RamLoc32
    
    PROVIDE(_pvHeapStart = DEFINED(__user_heap_base) ? __user_heap_base : .);
    PROVIDE(_vStackTop = DEFINED(__user_stack_top) ? __user_stack_top : __top_RamLoc32 - 0);
}
