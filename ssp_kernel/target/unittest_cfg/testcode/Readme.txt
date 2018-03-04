Prerequisites for configrator tests:
* gnm (binutils package)
* cunit (tested under version 2.1.2)

How to use:
1. Edit "SRCDIR" variable of Makefile in current directory(target/unittest_cfg/testcode).

2. To setup "base" directory files, run once:
	$ make setup

3. To test:
	$ make
To test an indivisual case separately, do like this:
	$ make cfgs/test_<test_name>_{suc|err}.t
example:
	$ make cfgs/test_cretsk_101_suc.t
	$ make cfgs/test_attini_102_err.t

4. To check result in result/ directory.
	Test_summary.txt : test result.
	"*.log" files : log data of commands and it's output.
	"*_err.log" : log data of commands' stderr output.

5. To cleanup temporary files,
	$ make clean
	or,  cleanup all files (include Makefile, sample1.* files in base/ directory)
	$ make cleanall
