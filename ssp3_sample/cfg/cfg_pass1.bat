
@echo Launch SSP Configurator(pass 1)

@rem pass1のコンフィギュレーション用バッチのオプション
@rem Kernel Dir:%1
@rem Application Configuration File:%2
@rem Application Include Path:%3

..\..\ssp_kernel\target\ccrlsim_ccrl\gen_cfg1_out_c.bat ../../ssp_kernel ../../ssp_kernel/sample/sample1.cfg ../../ssp_kernel/sample

