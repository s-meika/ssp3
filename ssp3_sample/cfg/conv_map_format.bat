
@echo Conver map file format from CS+ to GNU NM

@rem Build Dir:%1

ruby ..\..\ssp_kernel\arch\ccrl\convmap2nmfmt.rb %1\cfg_pass1.map %1\cfg1_out.syms
