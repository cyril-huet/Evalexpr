#!/bin/sh

PASSED=0
FAILED=0

test_error()
{
    expression="$1"
    mode="$2"

    echo "Test d'erreur : $expression"

    if [ "$mode" = "rpn" ]; then
        printf "%s\n" "$expression" | ./evalexpr -rpn >/dev/null 2>&1
    else
        printf "%s\n" "$expression" | ./evalexpr >/dev/null 2>&1
    fi

    if [ "$?" -ne 0 ]; then
        echo "Test réussi"
        PASSED=$((PASSED + 1))
    else
        echo "Test échoué"
        FAILED=$((FAILED + 1))
    fi
}

test_error "1 / 0" "infixe"
test_error "1 0 /" "rpn"
test_error "1 +" "infixe"
test_error "1 +" "rpn"
test_error "1 1 &" "rpn"

echo ""
echo "Tests réussis : $PASSED"
echo "Tests échoués : $FAILED"

if [ "$FAILED" -ne 0 ]; then
    exit 1
fi