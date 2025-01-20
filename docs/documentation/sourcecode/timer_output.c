// Configure TDC

TDC_init(&tdc_ele, &hspi1, SPI_CS_ELE_GPIO_Port, SPI_CS_ELE_Pin, TDC_ELE_ENABLE_GPIO_Port, TDC_ELE_ENABLE_Pin);
TDC_enable(&tdc_ele);

TDC_read(&tdc_ele, TDC_ADR_CONFIG1, data);
data[0] |= TDC_CONFIG1_MEAS_MODE_1;

TDC_write(&tdc_ele, TDC_ADR_CONFIG1, data);

while (1) {
    TDC_start(&tdc_ele);

    // Start Timer to toggle Pins from Low to High
    MX_TIM1_Init();
    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1); // START_ELE
    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_4); // STOP_ELE

    HAL_Delay(10); // 10 ms

    TDC_read_result(&tdc_ele, &tof_fs);

    sprintf(string, "ToF = %lu [ps]\n", (uint32_t)(tof_fs / 1000));
    HAL_UART_Transmit(&huart2, (uint8_t*)string, strlen(string), 10000);

    // Start Timer one more time to toggle Pins from High to Low (preparation for next iteration)
    MX_TIM1_Init();
    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1); // START_ELE
    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_4); // STOP_ELE

    HAL_Delay(10); // 10 ms
}
