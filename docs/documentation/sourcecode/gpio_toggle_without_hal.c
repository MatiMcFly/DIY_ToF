// Configure TDC

TDC_init(&tdc_ele, &hspi1, SPI_CS_ELE_GPIO_Port, SPI_CS_ELE_Pin, TDC_ELE_ENABLE_GPIO_Port, TDC_ELE_ENABLE_Pin);
TDC_enable(&tdc_ele);

TDC_read(&tdc_ele, TDC_ADR_CONFIG1, data);
data[0] |= TDC_CONFIG1_MEAS_MODE_2;

TDC_write(&tdc_ele, TDC_ADR_CONFIG1, data);

while (1) {
    TDC_start(&tdc_ele);

    // Set Pins to High with direct register access
    *((volatile uint32_t*)(GPIOA_BASE + 0x14)) |= (1 << 8);  // START_ELE
    *((volatile uint32_t*)(GPIOA_BASE + 0x14)) |= (1 << 11); // STOP_ELE

    TDC_read_result(&tdc_ele, &tof_fs);

    sprintf(string, "ToF = %lu [ps]\n", tof_fs / 1000);
    HAL_UART_Transmit(&huart2, (uint8_t *)string, strlen(string), 10000);

    // Set Pins to Low with direct register access (preparation for next iteration)
    *((volatile uint32_t*)(GPIOA_BASE + 0x14)) &= ~(1 << 8);  // START_ELE
    *((volatile uint32_t*)(GPIOA_BASE + 0x14)) &= ~(1 << 11); // STOP_ELE

    HAL_Delay(10); // 10 ms
}
