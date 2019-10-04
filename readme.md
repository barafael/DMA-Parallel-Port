# DMA Parallel Port

This project shows how you can use the DMA to drive one GPIO Port with values from a buffer array such that the CPU is completely unaffected.
The new values are written to the output port at triggers coming from timer updates.

This project uses C++, but integrates with and relies on the C files used by the STM32CubeIDE code generator.
