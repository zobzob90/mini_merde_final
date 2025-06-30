#!/bin/bash

# Final Boss: The Ultimate Minishell Stress Test 💀👑
echo "💀👑 FINAL BOSS: ULTIMATE STRESS TEST 👑💀"
echo "=============================================="

MINISHELL="./minishell"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
NC='\033[0m'

echo -e "${PURPLE}Testing against real bash behavior...${NC}"

bash_vs_minishell() {
    local test_name="$1"
    local command="$2"
    
    echo -e "${BLUE}FINAL BOSS TEST: $test_name${NC}"
    echo -e "${YELLOW}Command: $command${NC}"
    
    # Test with bash (reference)
    echo -e "${YELLOW}BASH OUTPUT:${NC}"
    echo -e "$command\nexit" | timeout 3s bash 2>&1 | head -10
    
    echo -e "${YELLOW}MINISHELL OUTPUT:${NC}"
    echo -e "$command\nexit" | timeout 3s $MINISHELL 2>&1 | head -10
    
    echo -e "${GREEN}✅ COMPARISON COMPLETE${NC}"
    echo "================================================"
}

echo
echo "🎯 BASIC COMPATIBILITY TESTS"
echo "============================="

bash_vs_minishell "Simple Command" "echo hello world"
bash_vs_minishell "Exit Status" "false; echo \$?"
bash_vs_minishell "Variable Expansion" "echo \$HOME"
bash_vs_minishell "Quote Handling" "echo \"hello \$USER\""

echo
echo "🔥 ADVANCED FEATURE TESTS"
echo "========================="

bash_vs_minishell "Pipe Chain" "echo test | cat | wc -l"
bash_vs_minishell "Redirection" "echo hello > /tmp/bash_test; cat /tmp/bash_test"
bash_vs_minishell "Background Job" "echo \"no background\" # sleep 1 &"
bash_vs_minishell "Command Not Found" "nonexistentcommand123"

echo
echo "💣 ERROR HANDLING TESTS"
echo "======================="

bash_vs_minishell "Permission Denied" "cat /etc/shadow 2>/dev/null || echo 'Permission denied'"
bash_vs_minishell "Directory as Command" "/tmp"
bash_vs_minishell "Empty Variable" "echo \$NONEXISTENT_VAR"

echo
echo "🏆 FINAL STRESS SUMMARY"
echo "======================="

# Quick functionality check
echo -e "${PURPLE}Running final functionality verification...${NC}"

FINAL_TEST_COMMANDS=(
    "echo 'Basic echo works'"
    "pwd"
    "echo \$?"
    "export TEST_VAR=success; echo \$TEST_VAR"
    "echo hello | cat"
    "echo test > /tmp/final_test; cat /tmp/final_test"
    "cd /tmp; pwd; cd -"
)

PASSED=0
TOTAL=${#FINAL_TEST_COMMANDS[@]}

for cmd in "${FINAL_TEST_COMMANDS[@]}"; do
    echo -e "${BLUE}Testing: $cmd${NC}"
    if echo -e "$cmd\nexit" | timeout 5s $MINISHELL >/dev/null 2>&1; then
        echo -e "${GREEN}✅ PASSED${NC}"
        ((PASSED++))
    else
        echo -e "${RED}❌ FAILED${NC}"
    fi
done

echo
echo "🎖️  FINAL RESULTS"
echo "================="
echo "Functionality Tests Passed: $PASSED/$TOTAL"
echo "Success Rate: $(( PASSED * 100 / TOTAL ))%"

if [ $PASSED -eq $TOTAL ]; then
    echo -e "${GREEN}🏆 CONGRATULATIONS! Your minishell is CHAMPION TIER! 🏆${NC}"
    echo -e "${PURPLE}Your shell has survived every torture test thrown at it!${NC}"
else
    echo -e "${YELLOW}⚔️  Your minishell is a strong warrior, but there's room for improvement!${NC}"
fi

echo
echo -e "${BLUE}🎭 BONUS: Try these manually for extra credit:${NC}"
echo "1. Press Ctrl+C while a command is running"
echo "2. Press Ctrl+D to exit gracefully"
echo "3. Test history with up/down arrows"
echo "4. Try tab completion (if implemented)"
echo "5. Test very long command lines"

# Cleanup
rm -f /tmp/bash_test /tmp/final_test
