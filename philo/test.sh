#!/bin/bash

# --- KONFIGURACJA ---
PHILO="./philo"
TIMEOUT_DURATION="5s"
# Valgrind: zwraca kod 42 jak znajdzie wyciek, -q żeby był cicho
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42 -q"

# --- KOLORY ---
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Błąd: Nie znaleziono pliku $PHILO${NC}"
    exit 1
fi

pass() { echo -e "[ ${GREEN}OK${NC} ] $1"; }
fail() { echo -e "[ ${RED}KO${NC} ] $1"; echo -e "      ${RED}Info: $2${NC}"; }
info() { echo -e "[ ${BLUE}INFO${NC} ] $1"; }

echo -e "${CYAN}=========================================${NC}"
echo -e "${CYAN}      PHILOSOPHERS TESTER PRO v2         ${NC}"
echo -e "${CYAN}=========================================${NC}"
echo ""

# ==============================================================================
# 1. TESTY LOGIKI (BEZ VALGRINDA - CZYSTA PRĘDKOŚĆ)
# ==============================================================================
echo -e "${YELLOW}--- 1. TESTY LOGIKI I CZASU (BEZ VALGRINDA) ---${NC}"

# A. CZY UMIERAJĄ?
check_death() {
    ARGS=$1
    DESC=$2
    OUT=$($PHILO $ARGS | grep "died" | wc -l)
    if [[ $OUT -eq 1 ]]; then pass "$DESC"; else fail "$DESC" "Oczekiwano 1 śmierci, wystąpiło: $OUT"; fi
}

check_death "1 800 200 200" "1 Filozof (Musi umrzeć)"
check_death "4 310 200 100" "Głodzenie (Die < Eat+Sleep)"

# B. CZY PRZEŻYWAJĄ?
check_survival() {
    ARGS=$1
    DESC=$2
    echo -n "Test: $ARGS ($DESC) ... "
    # Timeout symuluje nieskończoność. Jeśli grep znajdzie "died", to fail.
    timeout $TIMEOUT_DURATION $PHILO $ARGS > out.tmp 2>&1
    if grep -q "died" out.tmp; then
        echo -e "${RED}KO (Umarł)${NC}"
    else
        echo -e "${GREEN}OK (Przeżyli)${NC}"
    fi
    rm -f out.tmp
}

check_survival "4 410 200 200" "Standard"
check_survival "5 800 200 200" "Nieparzyści"
check_survival "4 450 200 200" "Na styk"

# C. LICZBA POSIŁKÓW
check_meals() {
    ARGS=$1
    echo -n "Test: $ARGS (Posiłki) ... "
    timeout 10s $PHILO $ARGS > out.tmp 2>&1
    RET=$?
    if grep -q "died" out.tmp; then
        echo -e "${RED}KO (Umarł przed zjedzeniem)${NC}"
    elif [[ $RET -eq 124 ]]; then
        echo -e "${RED}KO (Timeout - za wolno jedzą)${NC}"
    else
        echo -e "${GREEN}OK (Zjedli i wyszli)${NC}"
    fi
    rm -f out.tmp
}

check_meals "4 410 200 200 5"
check_meals "5 800 200 200 7"

echo ""

# ==============================================================================
# 2. TESTY PAMIEĆI PRZY BŁĘDACH (CZY ERROR ZWALNIA PAMIĘĆ?)
# ==============================================================================
echo -e "${YELLOW}--- 2. LEAKS CHECK: OBSŁUGA BŁĘDÓW ---${NC}"
info "Sprawdzamy, czy program zwalnia pamięć, gdy wystąpi błąd."

check_error_leaks() {
    ARGS=$1
    DESC=$2
    
    # Oczekujemy, że program zwróci błąd (!=0) ORAZ Valgrind zwróci 0 (brak wycieków).
    # Jeśli Valgrind znajdzie wyciek, zwróci 42.
    
    $VALGRIND $PHILO $ARGS > /dev/null 2> v_err.log
    VAL_RET=$?
    
    # Sprawdzamy czy Valgrind zgłosił wyciek (kod 42)
    if [[ $VAL_RET -eq 42 ]]; then
        fail "$DESC" "LEAKS DETECTED (Valgrind exit 42)"
        grep "definitely lost" v_err.log | head -n 1
    # Sprawdzamy czy był inny błąd krytyczny (np. segfault 139)
    elif [[ $VAL_RET -eq 139 ]]; then
        fail "$DESC" "SEGFAULT (Valgrind crash)"
    else
        pass "$DESC (Czysto)"
    fi
    rm -f v_err.log
}

check_error_leaks "0 800 200 200" "0 Filozofów"
check_error_leaks "4 -800 200 200" "Ujemne liczby"
check_error_leaks "4 800 200 a" "Litery w argumencie"

# Test zasobów (2000 wątków - program powinien wykryć błąd i wyjść czysto)
# Używamy mniejszej liczby niż 20k, żeby valgrind nie umarł, ale wystarczającej by sprawdzić sprzątanie
check_error_leaks "20000 800 200 200" "Zbyt wiele wątków (Resource Fail)"

echo ""

# ==============================================================================
# 3. TESTY PAMIĘCI PODCZAS SYMULACJI (SAFE MODE)
# ==============================================================================
echo -e "${YELLOW}--- 3. LEAKS CHECK: SYMULACJA ---${NC}"
info "Używamy bardzo dużego 'time_to_die', żeby powolny Valgrind nikogo nie zabił."

check_sim_leaks() {
    ARGS=$1
    DESC=$2
    
    echo -n "Test: $ARGS ... "
    
    # Timeout 15s, bo Valgrind mieli wolno
    timeout 20s $VALGRIND $PHILO $ARGS > /dev/null 2> v_err.log
    VAL_RET=$?
    
    # 42 = wyciek, 139 = segfault, 124 = timeout (przy testach infinite to OK, byle bez leaków)
    
    HAS_LEAK=0
    if [[ $VAL_RET -eq 42 ]] || grep -q "definitely lost" v_err.log; then HAS_LEAK=1; fi
    
    if [[ $HAS_LEAK -eq 1 ]]; then
         echo -e "${RED}KO (LEAKS)${NC}"
         grep "definitely lost" v_err.log | head -n 3
    elif [[ $VAL_RET -eq 139 ]]; then
         echo -e "${RED}KO (SEGFAULT)${NC}"
    else
         echo -e "${GREEN}OK (Czysto)${NC}"
    fi
    rm -f v_err.log
}

# Parametry "Safe Valgrind": Die=3000ms. Logic doesn't matter, memory does.
check_sim_leaks "4 3000 200 200 3" "Standardowy cykl jedzenia"
check_sim_leaks "5 3000 200 200 3" "Nieparzyści (cykl jedzenia)"
# Krótki test infinite (timeout go utnie, sprawdzamy czy po SIGTERM/kill valgrind coś zgłosi)
# Uwaga: Valgrind może nie zaraportować leaków jeśli zabijemy go timeoutem brutalnie (SIGKILL).
# Timeout wysyła SIGTERM, co jest ok.
check_sim_leaks "4 3000 200 200" "Nieskończona pętla (Safe Args)"

echo ""
echo -e "${CYAN}--- KONIEC TESTÓW ---${NC}"