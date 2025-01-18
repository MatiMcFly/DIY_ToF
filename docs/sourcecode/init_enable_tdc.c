TDC_init(&tdc_opt, &hspi1, SPI_CS_OPT_GPIO_Port, SPI_CS_OPT_Pin, TDC_OPT_ENABLE_GPIO_Port, TDC_OPT_ENABLE_Pin);

TDC_enable(&tdc_opt);
