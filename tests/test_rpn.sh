#!/bin/sh

PASSED=0
FAILED=0

test_expression()
{
    expected="$1"
    expression="$2"
    mode="$3"

    echo "Test de : $expression"

    if [ "$mode" = "rpn" ]; then
        result=$(printf "%s\n" "$expression" | ./evalexpr -rpn)
    else
        result=$(printf "%s\n" "$expression" | ./evalexpr)
    fi

    if [ "$result" = "$expected" ]; then
        echo "Test réussi"
        PASSED=$((PASSED + 1))
    else
        echo "Test échoué"
        echo "Attendu : $expected"
        echo "Obtenu : $result"
        FAILED=$((FAILED + 1))
    fi
}

test_invalid()
{
    expression="$1"

    echo "Test de : $expression"

    if printf "%s\n" "$expression" | ./evalexpr -rpn >/dev/null 2>&1; then
        echo "Test échoué"
        FAILED=$((FAILED + 1))
    else
        echo "Test réussi"
        PASSED=$((PASSED + 1))
    fi
}

test_expression 2 "1 + 1" "infixe"
test_expression 2 "1 1 +" "rpn"
test_expression 14 "2 3 4 * +" "rpn"
test_expression -6 "-2 3 *" "rpn"
test_expression 7 "10 3 -" "rpn"
test_expression 2 "8 4 /" "rpn"
test_invalid "1 +"

echo ""
echo "Tests réussis : $PASSED"
echo "Tests échoués : $FAILED"

if [ "$FAILED" -ne 0 ]; then
    exit 1
fi