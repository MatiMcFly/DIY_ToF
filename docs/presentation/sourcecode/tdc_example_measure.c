uint64_t tof_fs = 0;

while (1) {
    TDC_start(&tdc_ele);

    // Set Pins to High with direct register access
    *((volatile uint32_t*)(GPIOA_BASE + 0x14)) |= (1 << 8);  // START_ELE
    *((volatile uint32_t*)(GPIOA_BASE + 0x14)) |= (1 << 11); // STOP_ELE

    TDC_read_result(&tdc_ele, &tof_fs);

    // ToF result in [fs] is ready
}
