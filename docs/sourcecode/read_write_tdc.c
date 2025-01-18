TDC_read(&tdc_ele, TDC_ADR_CONFIG1, data);

data[0] |= TDC_CONFIG1_MEAS_MODE_2;

TDC_write(&tdc_ele, TDC_ADR_CONFIG1, data);
