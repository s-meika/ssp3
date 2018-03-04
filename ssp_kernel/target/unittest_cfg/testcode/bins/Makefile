TESTS = $(wildcard test_*.exe)

all:

.PHONY: $(TESTS)
$(TESTS):
	./$@ ../results/`basename $(@:.exe=)`

clean_commands :
	@rm -rf test_*.exe

