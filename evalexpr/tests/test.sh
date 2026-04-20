#!/bin/sh

BIN=./evalexpr
PASS=0
TOTAL=0

test_ok()
{
    TOTAL=$((TOTAL+1))
    INPUT="$1"
    EXPECT="$2"

    RESULT=$(echo "$INPUT" | $BIN 2>/dev/null)

    if [ "$RESULT" = "$EXPECT" ]; then
        echo "✅ OK: $INPUT = $EXPECT"
        PASS=$((PASS+1))
    else
        echo "❌ FAIL: $INPUT → got [$RESULT] expected [$EXPECT]"
    fi
}

test_rpn()
{
    TOTAL=$((TOTAL+1))
    INPUT="$1"
    EXPECT="$2"

    RESULT=$(echo "$INPUT" | $BIN -rpn 2>/dev/null)

    if [ "$RESULT" = "$EXPECT" ]; then
        echo "✅ OK RPN: $INPUT = $EXPECT"
        PASS=$((PASS+1))
    else
        echo "❌ FAIL RPN: $INPUT → got [$RESULT] expected [$EXPECT]"
    fi
}

test_err()
{
    TOTAL=$((TOTAL+1))
    INPUT="$1"

    echo "$INPUT" | $BIN >/dev/null 2>&1
    CODE=$?

    if [ "$CODE" -ne 0 ]; then
        echo "✅ ERR OK: $INPUT (code $CODE)"
        PASS=$((PASS+1))
    else
        echo "❌ FAIL ERR: $INPUT should fail"
    fi
}

echo "===== BASIC ====="
test_ok "1+1" "2"
test_ok "2*3" "6"
test_ok "10-4" "6"
test_ok "8/2" "4"
test_ok "9%2" "1"

echo "===== PRIORITY ====="
test_ok "2+3*4" "14"
test_ok "2*3+4" "10"
test_ok "2*3+4*5" "26"
test_ok "2+3*4+5" "19"

echo "===== PARENTHESES ====="
test_ok "(2+3)*4" "20"
test_ok "2*(3+4)" "14"
test_ok "(2+3)*(4+5)" "45"
test_ok "((2+3))" "5"

echo "===== POWER ====="
test_ok "2^3" "8"
test_ok "2^3^2" "512"
test_ok "(2^3)^2" "64"

echo "===== UNARY ====="
test_ok "-1+2" "1"
test_ok "--1" "1"
test_ok "---1" "-1"
test_ok "5*-2" "-10"
test_ok "5*--2" "10"
test_ok "86*--1" "86"

echo "===== MIXED ====="
test_ok "5*(2^2+3)" "35"
test_ok "10+2*3^2" "28"
test_ok "100/(5*5)" "4"
test_ok "7+8*2-3" "20"

echo "===== BIG ====="
test_ok "1000+2000" "3000"
test_ok "999*0" "0"
test_ok "12345+67890" "80235"

echo "===== RPN ====="
test_rpn "1 1 +" "2"
test_rpn "2 3 *" "6"
test_rpn "5 2 2 ^ 3 + *" "35"
test_rpn "10 2 /" "5"
test_rpn "2 3 4 * +" "14"

echo "===== ERRORS ====="
test_err "1/0"
test_err "1%0"
test_err "(1+2"
test_err "1+2)"
test_err "abc"
test_err "2++2"
test_err "*2+3"

echo "===== EDGE ====="
test_ok "0" "0"
test_ok "0001" "1"
test_ok "1+0" "1"
test_ok "0*999" "0"

echo "===== RESULT ====="
echo "$PASS / $TOTAL tests passed"

if [ "$PASS" -eq "$TOTAL" ]; then
    echo "ALL TESTS PASSED 🎉"
else
    echo "⚠️ SOME TESTS FAILED ⚠️ "
fi
