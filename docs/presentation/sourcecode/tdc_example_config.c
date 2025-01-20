// Configuration

TDC_init(&tdc_ele, &hspi1, SPI_CS_ELE_GPIO, TDC_ELE_ENABLE_GPIO);

TDC_enable(&tdc_ele);

// SPI Communication

TDC_read(&tdc_ele, TDC_ADR_CONFIG1, data);

data[0] |= TDC_CONFIG1_MEAS_MODE_1;

TDC_write(&tdc_ele, TDC_ADR_CONFIG1, data);
