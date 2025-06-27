#!/bin/bash

# EXTREME EDGE CASE TESTING 🔥💀
echo "🔥💀 EXTREME EDGE CASE TORTURE 💀🔥"
echo "===================================="

MINISHELL="./minishell"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

extreme_test() {
    local test_name="$1"
    local command="$2"
    local description="$3"
    
    echo -e "${BLUE}EXTREME TEST: $test_name${NC}"
    echo -e "${YELLOW}Command: $command${NC}"
    echo -e "${YELLOW}Testing: $description${NC}"
    
    echo -e "$command\nexit" | timeout 10s $MINISHELL 2>&1
    local exit_code=$?
    
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}❌ TIMEOUT${NC}"
    elif [ $exit_code -gt 128 ]; then
        echo -e "${RED}❌ CRASH${NC}"
    else
        echo -e "${GREEN}✅ SURVIVED THE EXTREME${NC}"
    fi
    echo "--------------------------------------------"
}

echo
echo "🌋 EXTREME HEREDOC TORTURE"
echo "=========================="

extreme_test "Massive Heredoc" "cat << EOF\n$(python3 -c "print('\\n'.join(['line ' + str(i) for i in range(1000)]))")\nEOF" "1000-line heredoc"

extreme_test "Nested Heredoc Delimiters" "cat << EOF\nThis is a test\n<< INNER\ninner content\nINNER\nEOF" "Nested-like heredoc content"

extreme_test "Heredoc with Special Characters" "cat << 'END'\n\$HOME \$(whoami) \`date\` \"quotes\" 'quotes'\nEND" "Heredoc with shell metacharacters"

echo
echo "🧨 EXTREME PIPE CHAOS"
echo "===================="

extreme_test "100 Pipe Chain" "echo test$(for i in {1..100}; do echo -n ' | cat'; done)" "100-command pipe chain"

extreme_test "Broken Pipe Handling" "yes | head -1" "Broken pipe scenario"

extreme_test "Pipe with Large Data" "head -c 1048576 /dev/zero | wc -c" "1MB through pipe"

echo
echo "⚡ EXTREME VARIABLE EXPANSION"
echo "============================"

extreme_test "Recursive Variable Reference" "export A=\$B; export B=\$A; echo \$A" "Circular variable reference"

extreme_test "Variable in Variable Name" "export TEST123=hello; VAR=123; echo \$TEST\$VAR" "Dynamic variable name"

extreme_test "Extreme Variable Nesting" "echo \${\${\${\$HOME}}}" "Deeply nested variable syntax"

echo
echo "🎯 EXTREME QUOTE EDGE CASES"
echo "============================"

extreme_test "Quote Inception" "echo \"'\"\\'\"'\"" "Complex quote nesting"

extreme_test "Escaped Quote Madness" "echo \"\\\"\\\"\\\"\\\"\"" "Multiple escaped quotes"

extreme_test "Mixed Quote with Variables" "echo '\$HOME'\" and \"\\\$USER" "Mixed quotes with variables and escapes"

echo
echo "💣 EXTREME FILE OPERATIONS"
echo "=========================="

# Create a file with problematic name
touch "/tmp/file with spaces and 'quotes' and \"double quotes\""

extreme_test "Problematic Filename" "cat \"/tmp/file with spaces and 'quotes' and \\\"double quotes\\\"\"" "File with special characters in name"

extreme_test "Permission Denied" "cat /etc/shadow" "Permission denied scenario"

extreme_test "Non-existent Deep Path" "cat /non/existent/very/deep/path/file.txt" "Deep non-existent path"

echo
echo "🌪️ EXTREME REDIRECTION MAYHEM"
echo "=============================="

extreme_test "Multiple Output Redirects" "echo test > /tmp/out1 > /tmp/out2 > /tmp/out3 > /tmp/out4" "Many output redirections"

extreme_test "Circular Redirection" "cat < /tmp/circular > /tmp/circular" "Circular file redirection"

extreme_test "Redirect to Directory" "echo test > /tmp" "Redirect to directory (should fail)"

echo
echo "🎪 EXTREME BUILTIN STRESS"
echo "========================="

extreme_test "CD to Current Dir Loop" "cd .; cd .; cd .; cd .; cd ." "Multiple cd to current directory"

extreme_test "Export Massive Variable" "export HUGE=\$(python3 -c \"print('X' * 10000)\")" "Export huge variable"

extreme_test "Unset System Variable" "unset PATH; echo test" "Unset critical variable"

echo
echo "🎭 EXTREME SIGNAL INTERFERENCE"
echo "=============================="

extreme_test "Command During Signal" "sleep 5 &" "Background process creation"

echo
echo "🔥 EXTREME MEMORY PRESSURE"
echo "=========================="

extreme_test "Memory Bomb Command" "echo \$(seq 1 10000)" "Command substitution with huge output"

extreme_test "Argument Explosion" "echo \$(seq 1 1000 | tr '\\n' ' ')" "Massive argument list"

echo
echo "👹 EXTREME EVIL INPUTS"
echo "======================"

extreme_test "Null Byte Injection" "echo -e \"hello\\x00world\"" "Null byte in input"

extreme_test "Binary Data Command" "echo \$(head -c 100 /dev/urandom | base64)" "Binary data as command"

extreme_test "Infinite Loop Command" "while true; do echo test; done" "Potential infinite loop (will timeout)"

echo
echo "🎯 EXTREME EDGE COMBINATIONS"
echo "============================"

extreme_test "Everything At Once" "export TEST=\$(echo \"complex \\\$HOME\"); echo \"\$TEST\" | cat > /tmp/complex_test && cat < /tmp/complex_test | wc -l" "Complex combination"

extreme_test "Nested Command Substitution" "echo \$(echo \$(echo \$(echo nested)))" "Deep command substitution nesting"

echo
echo "🏁 EXTREME TESTING COMPLETE"
echo "============================"
echo "If your minishell survived all of these, it's absolutely bulletproof! 🛡️"

# Cleanup
rm -f "/tmp/file with spaces and 'quotes' and \"double quotes\""
rm -f /tmp/out1 /tmp/out2 /tmp/out3 /tmp/out4 /tmp/circular /tmp/complex_test
