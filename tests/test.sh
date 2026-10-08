#!/bin/sh

PASSED=0
FAILED=0

if [ -t 1 ]; then
    GREEN=$(printf '\033[32m')
    RED=$(printf '\033[31m')
    BLUE=$(printf '\033[34m')
    RESET=$(printf '\033[0m')
else
    GREEN=""
    RED=""
    BLUE=""
    RESET=""
fi

test_value()
{
    label="$1"
    expected="$2"
    expression="$3"
    mode="$4"

    if [ "$mode" = "rpn" ]; then
        result=$(printf "%s\n" "$expression" | ./evalexpr -rpn)
    else
        result=$(printf "%s\n" "$expression" | ./evalexpr)
    fi

    status=$?

    if [ "$status" -eq 0 ] && [ "$result" = "$expected" ]; then
        printf "  %s[OK]%s   %s\n" "$GREEN" "$RESET" "$label"
        printf "          %s -> %s\n" "$expression" "$result"
        PASSED=$((PASSED + 1))
    else
        printf "  %s[FAIL]%s %s\n" "$RED" "$RESET" "$label"
        printf "          expression : %s\n" "$expression"
        printf "          attendu    : %s\n" "$expected"
        printf "          obtenu     : %s\n" "$result"
        FAILED=$((FAILED + 1))
    fi
}

test_error()
{
    label="$1"
    expression="$2"
    mode="$3"

    if [ "$mode" = "rpn" ]; then
        printf "%s\n" "$expression" | ./evalexpr -rpn >/dev/null 2>&1
    else
        printf "%s\n" "$expression" | ./evalexpr >/dev/null 2>&1
    fi

    status=$?

    if [ "$status" -ne 0 ]; then
        printf "  %s[OK]%s   %s\n" "$GREEN" "$RESET" "$label"
        printf "          %s -> erreur détectée\n" "$expression"
        PASSED=$((PASSED + 1))
    else
        printf "  %s[FAIL]%s %s\n" "$RED" "$RESET" "$label"
        FAILED=$((FAILED + 1))
    fi
}

test_invalid_argument()
{
    ./evalexpr --invalid >/dev/null 2>&1

    if [ "$?" -ne 0 ]; then
        printf "  %s[OK]%s   argument invalide\n" "$GREEN" "$RESET"
        PASSED=$((PASSED + 1))
    else
        printf "  %s[FAIL]%s argument invalide\n" "$RED" "$RESET"
        FAILED=$((FAILED + 1))
    fi
}

printf "%s\n" "========================================"
printf "       %sEvalexpr - tests%s\n" "$BLUE" "$RESET"
printf "%s\n\n" "========================================"

printf "%s\n" "--- Expressions classiques ---"
test_value "addition" 2 "1 + 1" "infixe"
test_value "priorité des opérations" 14 "2 + 3 * 4" "infixe"
test_value "parenthèses" 20 "(2 + 3) * 4" "infixe"
test_value "nombre négatif" -3 "-5 + 2" "infixe"
test_value "modulo" 1 "10 % 3" "infixe"
test_value "puissance" 8 "2 ^ 3" "infixe"
test_value "soustraction" 5 "8 - 3" "infixe"
test_value "multiplication" 42 "6 * 7" "infixe"
test_value "division" 4 "20 / 5" "infixe"
test_value "puissance avec multiplication" 16 "2 ^ 3 * 2" "infixe"
test_value "puissances associatives à droite" 512 "2 ^ 3 ^ 2" "infixe"
test_value "parenthèses imbriquées" 15 "((2 + 3) * (4 - 1))" "infixe"
test_value "espaces supplémentaires" 4 "  12   /  3 " "infixe"
test_value "négatif après parenthèse" 9 "(-2 + 5) * 3" "infixe"
test_value "deux signes négatifs" 5 "--5" "infixe"
test_value "signe positif" 8 "+7 + 1" "infixe"
test_value "divisions successives" 10 "100 / 5 / 2" "infixe"
test_value "plusieurs opérateurs" 16 "18 - 2 * 3 + 4" "infixe"
test_value "nombre négatif entre parenthèses" 1 "(3+-2)" "infixe"

printf "\n%s\n" "--- Expressions RPN ---"
test_value "addition RPN" 2 "1 1 +" "rpn"
test_value "plusieurs opérations" 14 "2 3 4 * +" "rpn"
test_value "soustraction" 3 "5 2 -" "rpn"
test_value "nombre négatif" -6 "-2 3 *" "rpn"
test_value "puissance RPN" 8 "2 3 ^" "rpn"
test_value "multiplication RPN" 42 "6 7 *" "rpn"
test_value "division RPN" 4 "20 5 /" "rpn"
test_value "modulo RPN" 4 "14 5 %" "rpn"
test_value "puissances RPN" 512 "2 3 2 ^ ^" "rpn"
test_value "espaces RPN" 5 "2	3	+" "rpn"
test_value "nombre seul RPN" 42 "42" "rpn"

printf "\n%s\n" "--- Erreurs ---"
test_error "expression incomplète" "1 +" "infixe"
test_error "division par zéro" "1 0 /" "rpn"
test_error "opérateur inconnu" "1 1 &" "rpn"
test_error "division par zéro infixe" "1 / 0" "infixe"
test_error "modulo par zéro" "1 % 0" "infixe"
test_error "parenthèse non fermée" "(1 + 2" "infixe"
test_error "parenthèse en trop" "1 + 2)" "infixe"
test_error "opérande manquant en infixe" "1 2" "infixe"
test_error "opérande manquant en RPN" "1 +" "rpn"
test_invalid_argument

printf "\n%s\n" "========================================"
printf "Tests réussis : %s\n" "$PASSED"
printf "Tests échoués : %s\n" "$FAILED"
printf "%s\n" "========================================"

if [ "$FAILED" -ne 0 ]; then
    exit 1
fi

