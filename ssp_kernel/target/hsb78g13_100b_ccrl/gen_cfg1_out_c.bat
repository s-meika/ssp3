
@echo Kernel Dir:%1
@echo Configuration File:%2
@echo Application Include Path:%3

ruby -Eutf-8:utf-8 %1/cfg/cfg.rb --pass 1 --kernel ssp -I%1 -I%1/include -I%1/arch -I.. -I%1/target/ccrlsim_ccrl -I%1/arch/rl78_ccrl/ -I%1/arch/ccrl/ -I%3  --api-table %1/kernel/kernel_api.def --symval-table %1/kernel/kernel_sym.def --symval-table %1/syssvc/syssvc_sym.def --symval-table %1/arch/rl78_ccrl/prc_sym.def --symval-table %1/arch/rl78_ccrl/rl78_g13/chip_sym.def %2


@rem../target/ccrlsim_ccrl/target_kernel.cfg %2
