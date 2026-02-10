#!/bin/sh


if echo "1+1" | ./evalexpr  | grep -q '^2$'; then
    echo "Test reussie"
    fi
if echo "1*1" | ./evalexpr  | grep -q '^1$'; then
    echo "Test reussie"
    fi   

if echo "86*--1" | ./evalexpr  | grep -q '^86$'; then
    echo "Test reussie"
    fi

if echo "86/1" | ./evalexpr  | grep -q '^86$'; then
    echo "Test reussie"
    fi

    if echo "2^3" | ./evalexpr  | grep -q '^8$'; then
    echo "Test reussie"
    fi

echo "1 1 +" | ./evalexpr -rpn
echo "5 2 2 ^ 3 + *" | ./evalexpr -rpn | cat -e
echo "5*(2^2+3)" | ./evalexpr | cat -e
