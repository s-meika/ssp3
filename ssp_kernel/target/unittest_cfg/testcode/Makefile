#
#  TOPPERS/SSP Kernel
#      Toyohashi Open Platform for Embedded Real-Time Systems/
#      Smallest Set Profile Kernel
# 
#  Copyright (C) 2012 by Naoki Saito
#              Nagoya Municipal Industrial Research Institute, JAPAN
# 
#  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
# 
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
# 
# 

#
# コンフィギュレーションのテスト
#

##### 変数定義

# SSP のトップディレクトリ
SRCDIR = ../../..
# 使用するターゲット依存部
TARGET = unittest_cfg

# コンフィギュレーションに成功するテストケースの集まり
TESTCFGS = $(wildcard cfgs/test_*_suc.cfg)
CFGTESTS = $(TESTCFGS:.cfg=.t)
TESTFILES = $(TESTCFGS: _suc.cfg=.c)

# コンフィギュレーション失敗するテストケースの集まり
ERRTESTCFGS = $(wildcard cfgs/test_*_err.cfg)
ERRCFGTESTS = $(ERRTESTCFGS:.cfg=.t)

##### テストの実行

# コンフィギュレーションの実行
# Todo: cfgs/*.cfg だけでなく tests/*.c ファイルの変更にも依存するようにしたい

all: success_case error_case

success_case: $(CFGTESTS)
error_case: $(ERRCFGTESTS)

# コンフィギュレーションが成功する場合のテスト
# 主に，出力された変数やマクロの値が正しいかどうかの確認．
# 関数を出力するケースについては，その関数の実行順序，実行回数，引数の正しさも確認する．
$(CFGTESTS): %.t : %.cfg
	@echo "---- Test (`basename $(@:_suc.t=)`)"
	@$(MAKE) -C cfgs APPLNAME=`basename $(@:.t=)` generate_configfiles > results/`basename $(@:_suc.t=)`.log 2> results/`basename $(@:_suc.t=)`_err.log
	@cd cfgs && mv kernel_cfg.c `basename $(@:_suc.t=)`_kernel_cfg.c
	@$(MAKE) -C tests main.o >> results/`basename $(@:_suc.t=)`.log 2>> results/`basename $(@:_suc.t=)`_err.log
	@$(MAKE) -C tests `basename $(@:_suc.t=.o)` >> results/`basename $(@:_suc.t=)`.log 2>> results/`basename $(@:_suc.t=)`_err.log
	@$(MAKE) -C tests `basename $(@:_suc.t=)`_kernel_cfg.o >> results/`basename $(@:_suc.t=)`.log 2>> results/`basename $(@:_suc.t=)`_err.log
	@$(MAKE) -C tests `basename $(@:_suc.t=)`.exe >> results/`basename $(@:_suc.t=)`.log 2>> results/`basename $(@:_suc.t=)`_err.log
	@cd cfgs && mv kernel_cfg.h `basename $(@:_suc.t=)`_kernel_cfg.h
	@$(MAKE) -C bins `basename $(@:_suc.t=)`.exe >> results/`basename $(@:_suc.t=)`.log 2>> results/`basename $(@:_suc.t=)`_err.log
	@echo "---- Result (`basename $(@:_suc.t=)`)"  >> results/test_summary.txt
	@awk '/Run Summary:/ { print $0 }' results/`basename $(@:_suc.t=)`.log >> results/test_summary.txt
	@awk '/asserts/ { print $0 }' results/`basename $(@:_suc.t=)`.log >> results/test_summary.txt
	@touch $*.t

# コンフィギュレーションエラーが発生する場合のテスト
# 主に，出力されるエラーコードが正しいかどうかの確認．
$(ERRCFGTESTS): %.t : %.cfg
	@echo "---- Error Case Test. Check is not performed automatically."
	@echo "---- Test (`basename $(@:_err.t=)`)."
	-@$(MAKE) -C cfgs APPLNAME=`basename $(@:.t=)` generate_configfiles > results/`basename $(@:_err.t=)`.log 2> results/`basename $(@:_err.t=)`_err.log
	@awk '/cfg:.+:.+: error:/ { print $0 }' results/`basename $(@:_err.t=)`_err.log
	@touch $*.t

#####

# 作業準備．最初に1回だけ実行する．
# 　base ディレクトリへ移動し，configureスクリプトを実行する
# 　スクリプトにより base 以下にソースコードが生成される．
setup:
	chmod +x $(SRCDIR)/configure
	cd base && ../$(SRCDIR)/configure -T $(TARGET)

#####

# 生成した全ファイルを削除
clean:
	@$(MAKE) -C cfgs clean_cfgs
	@$(MAKE) -C tests clean_codes
	@$(MAKE) -C bins clean_commands
	@cd results && rm -rf *.{xml,log} test_summary.txt

# clean に加え，setup で生成した base 以下のファイルも全て削除．
cleanall: clean
	cd base && rm -rf Makefile* sample1.* svccall.def
