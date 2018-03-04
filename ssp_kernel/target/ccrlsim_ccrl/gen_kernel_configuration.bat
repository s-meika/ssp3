
@echo Kernel Dir:%1
@echo Application Include Path:%2

ruby %1/cfg/cfg.rb --pass 2 --kernel ssp -I%1 -I%1/include -I%1/arch -I%1/target/ccrlsim_ccrl -I%1/arch/rl78_ccrl/ -I%1/arch/rl78_ccrl/rl78_g13 -I%1/arch/ccrl/ -I%2 -T %1/target/ccrlsim_ccrl/target_kernel.trb

@rem ruby -Eutf-8:utf-8 ../cfg/cfg.rb --pass 2 --kernel ssp -I. -I../include -I../arch  -I../target/cq_frk_fm3_gcc -I../arch/arm_m_gcc/ -I.. -I../sample -I./gen -I../tecs_kernel -T ../target/ccrlsim_ccrl/target_kernel.trb

