uint64_t tof_fs = 0;

TDC_start(&tdc_opt);

/* ... generate start and stop signals */

if (TDC_read_result(&tdc_opt, &tof_fs) != TDC_OK) {
    for (;;) {} // Error handling...
}

/* tof_fs now holds the measurement result, in [fs] */
