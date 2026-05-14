# The command-line Scheme interpreter
SCHEME ?= plt-r5rs

# Tests for use with token-types-tester.scm: all files that end with
# tokens.in
# Expected output must have the .in replaced with .expect
TEST_TOKEN_INPUTS ?= $(wildcard *tokens.in)

# Error tests for use with token-types-tester.scm: all files that end
# with tokens.err
TEST_TOKEN_ERRORS ?= $(wildcard *tokens.err)

# Tests for use with tokenize-tester.scm and parse-tester.scm
# More files can be added after distribution.scm, separated by spaces
# Expected output must have the filename with .scm replaced by
# .tokens.expect (e.g. distribution.tokens.expect) and .datums.expect
# (e.g. distribution.datums.expect)
TEST_SCHEME_INPUTS ?= distribution.scm public_tests.scm $(wildcard test*.scm)

# Tests for use with read-simple-tester.scm: all files that end with
# simple.in
# Expected output must have the .in replaced with .expect
TEST_SIMPLE_INPUTS ?= $(wildcard *simple.in)

# Tests for use with read-compound-tester.scm: all files that end with
# compound.in
# Expected output must have the .in replaced with .expect
TEST_COMPOUND_INPUTS ?= $(wildcard *compound.in)

# Tests for use with read-datum-tester.scm: all files that end with
# datum.in
# Expected output must have the .in replaced with .expect
TEST_DATUM_INPUTS ?= $(wildcard *datum.in)

# Error tests for use with read-datum-tester.scm: all files that end
# with datum.err
TEST_DATUM_ERRORS ?= $(wildcard *datum.err)

# Function to check for and warn about missing expected output
check_expected = (test -f $(1) || \
	(echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"; \
	echo "WARNING: missing expected output file" $(1) ; \
	echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"; \
	false))

# Function to check for expected output and do diff
check_and_diff = ! $(call check_expected,$(1).expect) || \
	(echo diff $(1).out $(1).expect ; diff $(1).out $(1).expect)

all: done

correct-tests: test-tokens test-tokenize test-simple test-compound test-datum test-parse

error-tests: error-tokens error-datum

phase1: test-tokens error-tokens

phase2: test-tokenize

phase3: test-simple test-compound test-datum test-parse

test-tokens: $(TEST_TOKEN_INPUTS:.in=.tokens)

%.tokens:
	$(SCHEME) token-types-tester.scm < $*.in > $*.out
	diff $*.out $*.expect

test-tokenize: $(TEST_SCHEME_INPUTS:%.scm=%.tokenize)

%.tokenize:
	$(SCHEME) tokenize-tester.scm < $*.scm | sed "s/^Error:.*$$/Error:/g" > $*.tokens.out
	@$(call check_and_diff,$*.tokens)

test-simple: $(TEST_SIMPLE_INPUTS:.in=.simple)

%.simple:
	$(SCHEME) read-simple-tester.scm < $*.in > $*.out
	diff $*.out $*.expect

test-compound: $(TEST_COMPOUND_INPUTS:.in=.compound)

%.compound:
	$(SCHEME) read-compound-tester.scm < $*.in > $*.out
	diff $*.out $*.expect

test-datum: $(TEST_DATUM_INPUTS:.in=.datum)

%.datum:
	$(SCHEME) read-datum-tester.scm < $*.in > $*.out
	diff $*.out $*.expect

test-parse: $(TEST_SCHEME_INPUTS:%.scm=%.parse)

%.parse:
	$(SCHEME) parse-tester.scm < $*.scm | sed "s/^Error:.*$$/Error:/g" > $*.datums.out
	@$(call check_and_diff,$*.datums)

error-tokens: $(TEST_TOKEN_ERRORS:.err=.err-tokens)

%.err-tokens:
	$(SCHEME) token-types-tester.scm < $*.err > $*.out
	diff -I "Error: .*" $*.out $*.expect
	grep -q '^Error: ' $*.out
	echo PASS

error-datum: $(TEST_DATUM_ERRORS:.err=.err-datum)

%.err-datum:
	$(SCHEME) read-datum-tester.scm < $*.err > $*.out
	diff -I "Error: .*" $*.out $*.expect
	grep -q '^Error: ' $*.out
	echo PASS

done: correct-tests error-tests
	@echo '##### All tests passed! #####'

clean:
	rm -vf *.out
