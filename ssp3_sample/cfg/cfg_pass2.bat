
@echo Launch SSP Configurator(pass 2)

@rem ���̃o�b�`�t�@�C���̃I�v�V����
@rem Build Directory:%1

@echo Conver map file format from CS+ to GNU NM

@rem Build Dir:%1

ruby ..\..\ssp_kernel\arch\ccrl\convmap2nmfmt.rb %1\cfg.map %1\cfg1_out.syms


@rem pass2�̃R���t�B�M�����[�V�����p�o�b�`�̃I�v�V����
@rem Kernel Dir:%1
@rem Application Include Path:%2


copy %1\cfg1_out.srec .
copy %1\cfg1_out.syms .

..\..\ssp_kernel\target\hsb78g13_100b_ccrl\gen_kernel_configuration.bat ../../ssp_kernel ../../ssp_kernel/sample

copy kernel_cfg.h kernel_cfg.c %1
