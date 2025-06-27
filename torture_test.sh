#!/bin/bash

# Minishell Torture Test Suite 🔥
# This script will push your minishell to its absolute limits

echo "🔥 MINISHELL TORTURE CHAMBER 🔥"
echo "=================================="
echo

MINISHELL="./minishell"
TEST_COUNT=0
FAILED_TESTS=0

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

run_test() {
    local test_name="$1"
    local command="$2"
    local expected_behavior="$3"
    
    TEST_COUNT=$((TEST_COUNT + 1))
    echo -e "${BLUE}Test $TEST_COUNT: $test_name${NC}"
    echo -e "${YELLOW}Command: $command${NC}"
    echo -e "${YELLOW}Expected: $expected_behavior${NC}"
    
    # Run the command with timeout to prevent hanging
    echo "$command" | timeout 5s $MINISHELL 2>&1
    local exit_code=$?
    
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}❌ TIMEOUT - Test hung for 5 seconds${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    elif [ $exit_code -ne 0 ] && [ $exit_code -ne 1 ]; then
        echo -e "${RED}❌ CRASH - Exit code: $exit_code${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    else
        echo -e "${GREEN}✅ Survived${NC}"
    fi
    echo "----------------------------------------"
}

run_interactive_test() {
    local test_name="$1"
    local commands="$2"
    local expected_behavior="$3"
    
    TEST_COUNT=$((TEST_COUNT + 1))
    echo -e "${BLUE}Interactive Test $TEST_COUNT: $test_name${NC}"
    echo -e "${YELLOW}Commands: $commands${NC}"
    echo -e "${YELLOW}Expected: $expected_behavior${NC}"
    
    # Create a temporary file with commands
    echo -e "$commands\nexit" > /tmp/minishell_test_commands
    
    # Run with timeout
    timeout 10s $MINISHELL < /tmp/minishell_test_commands 2>&1
    local exit_code=$?
    
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}❌ TIMEOUT - Test hung for 10 seconds${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    elif [ $exit_code -gt 128 ]; then
        echo -e "${RED}❌ CRASH - Exit code: $exit_code${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    else
        echo -e "${GREEN}✅ Survived${NC}"
    fi
    
    rm -f /tmp/minishell_test_commands
    echo "----------------------------------------"
}

echo "🧪 BASIC FUNCTIONALITY TESTS"
echo "============================="

run_interactive_test "Simple echo" "echo hello world" "Should print hello world"
run_interactive_test "Echo with quotes" "echo \"hello world\"" "Should print hello world"
run_interactive_test "Echo with single quotes" "echo 'hello world'" "Should print hello world"
run_interactive_test "PWD command" "pwd" "Should print current directory"
run_interactive_test "CD and PWD" "cd /tmp\npwd" "Should change to /tmp and print it"

echo
echo "💥 STRESS TESTS - ARGUMENT LIMITS"
echo "=================================="

# Test with many arguments
LONG_ARGS=""
for i in {1..1000}; do
    LONG_ARGS="$LONG_ARGS arg$i"
done
run_interactive_test "1000 arguments to echo" "echo $LONG_ARGS" "Should handle many arguments"

# Test with very long single argument
LONG_STRING=$(python3 -c "print('A' * 10000)")
run_interactive_test "Very long string" "echo \"$LONG_STRING\"" "Should handle very long string"

echo
echo "🔥 QUOTE TORTURE TESTS"
echo "======================"

run_interactive_test "Nested quotes 1" "echo \"'hello'\"" "Should handle nested quotes"
run_interactive_test "Nested quotes 2" "echo '\"hello\"'" "Should handle nested quotes"
run_interactive_test "Unclosed quote" "echo \"hello" "Should handle unclosed quote gracefully"
run_interactive_test "Multiple quote types" "echo \"hello\" 'world' test" "Should handle mixed quotes"
run_interactive_test "Empty quotes" "echo \"\" ''" "Should handle empty quotes"
run_interactive_test "Quote hell" "echo \"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"" "Should survive quote hell"

echo
echo "💀 VARIABLE EXPANSION TORTURE"
echo "=============================="

run_interactive_test "Basic variable" "echo \$HOME" "Should expand HOME variable"
run_interactive_test "Non-existent variable" "echo \$NONEXISTENT" "Should handle non-existent variable"
run_interactive_test "Variable in quotes" "echo \"\$HOME\"" "Should expand variable in quotes"
run_interactive_test "Variable not in single quotes" "echo '\$HOME'" "Should not expand in single quotes"
run_interactive_test "Exit status variable" "echo \$?" "Should show exit status"
run_interactive_test "Complex variable expansion" "echo \$HOME/\$USER/\$PWD" "Should handle multiple variables"
run_interactive_test "Variable with braces" "echo \${HOME}" "Should handle braced variables"

echo
echo "🌪️ REDIRECTION TORTURE"
echo "======================="

run_interactive_test "Basic output redirect" "echo hello > /tmp/test_output" "Should redirect to file"
run_interactive_test "Append redirect" "echo world >> /tmp/test_output" "Should append to file"
run_interactive_test "Input redirect" "cat < /tmp/test_output" "Should read from file"
run_interactive_test "Multiple redirections" "echo test > /tmp/out1 > /tmp/out2" "Should handle multiple redirections"
run_interactive_test "Redirect to /dev/null" "echo test > /dev/null" "Should redirect to null"

echo
echo "🔗 PIPE TORTURE CHAMBER"
echo "======================="

run_interactive_test "Simple pipe" "echo hello | cat" "Should pipe echo to cat"
run_interactive_test "Multiple pipes" "echo hello | cat | cat | cat" "Should handle multiple pipes"
run_interactive_test "Pipe with grep" "echo -e \"hello\\nworld\" | grep hello" "Should pipe to grep"
run_interactive_test "Long pipe chain" "echo test | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat" "Should handle long pipe chain"

echo
echo "🎭 BUILTIN COMMAND TORTURE"
echo "=========================="

run_interactive_test "CD with spaces" "cd \"/tmp/test dir with spaces\"" "Should handle spaces in path"
run_interactive_test "CD to non-existent" "cd /non/existent/path" "Should handle non-existent directory"
run_interactive_test "Export with equals" "export TEST=value" "Should set environment variable"
run_interactive_test "Export without equals" "export TEST" "Should handle export without value"
run_interactive_test "Echo with -n flag" "echo -n hello" "Should handle -n flag"
run_interactive_test "Echo with multiple flags" "echo -n -e \"hello\\nworld\"" "Should handle multiple flags"

echo
echo "🚀 COMMAND EXECUTION TORTURE"
echo "============================"

run_interactive_test "Non-existent command" "nonexistentcommand123" "Should handle command not found"
run_interactive_test "Command with many args" "ls -la -h -t -r -S -1" "Should handle many flags"
run_interactive_test "Empty command" "" "Should handle empty input"
run_interactive_test "Only spaces" "   " "Should handle only spaces"
run_interactive_test "Command with path" "/bin/echo hello" "Should execute with full path"

echo
echo "😈 EVIL INPUT TESTS"
echo "==================="

run_interactive_test "Semicolon separated" "echo hello; echo world" "Should handle semicolons"
run_interactive_test "Ampersand (background)" "echo hello &" "Should handle background processes"
run_interactive_test "Control characters" "echo -e \"\\x01\\x02\\x03\"" "Should handle control characters"
run_interactive_test "Unicode characters" "echo \"🔥💀🎭\"" "Should handle unicode"
run_interactive_test "Very long command line" "$(python3 -c "print('echo ' + 'a' * 1000)")" "Should handle very long command"

echo
echo "💣 MEMORY TORTURE TESTS"
echo "======================="

# Test with many commands in sequence
MANY_COMMANDS=""
for i in {1..100}; do
    MANY_COMMANDS="$MANY_COMMANDS\necho test$i"
done
run_interactive_test "100 sequential commands" "$MANY_COMMANDS" "Should handle many sequential commands"

echo
echo "🎪 SIGNAL HANDLING TESTS"
echo "========================"

echo "Note: Signal tests require manual intervention"
echo "Try these manually:"
echo "1. Start minishell and press Ctrl+C (should not exit)"
echo "2. Start minishell and press Ctrl+D (should exit gracefully)"
echo "3. Start minishell and press Ctrl+Z (should handle properly)"

echo
echo "📊 TEST SUMMARY"
echo "==============="
echo "Total tests run: $TEST_COUNT"
echo "Failed tests: $FAILED_TESTS"
echo "Success rate: $(( (TEST_COUNT - FAILED_TESTS) * 100 / TEST_COUNT ))%"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! Your minishell is a survivor! 🎉${NC}"
else
    echo -e "${RED}💥 $FAILED_TESTS tests failed. Time to debug! 💥${NC}"
fi

# Cleanup
rm -f /tmp/test_output /tmp/out1 /tmp/out2
