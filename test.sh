#!/bin/bash
# test.sh — version corrigée

make re > /dev/null 2>&1 && echo "✅ build OK" || { echo "❌ build FAIL"; exit 1; }

run_no_die() {
    local desc="$1"; shift
    timeout 10 ./philo "$@" > /tmp/philo_out 2>&1
    local rc=$?
    if [ $rc -eq 124 ] && ! grep -q "died" /tmp/philo_out; then
        echo "  ✅ $desc — no death in 10s"
    else
        echo "  ❌ $desc — rc=$rc, lines=$(wc -l < /tmp/philo_out), died=$(grep -c died /tmp/philo_out)"
    fi
}

run_must_eat() {
    local desc="$1"; shift
    ./philo "$@" > /tmp/philo_out 2>&1
    if ! grep -q "died" /tmp/philo_out; then
        echo "  ✅ $desc — clean stop, no death"
    else
        echo "  ❌ $desc — saw a death"
    fi
}

run_must_die() {
    local desc="$1"; shift
    local last=$(timeout 5 ./philo "$@" 2>&1 | tail -1)
    if echo "$last" | grep -q "died"; then
        echo "  ✅ $desc — $last"
    else
        echo "  ❌ $desc — last line: $last"
    fi
}

check_no_log_after_died() {
    local desc="$1"; shift
    timeout 5 ./philo "$@" > /tmp/philo_out 2>&1
    local last=$(tail -1 /tmp/philo_out)
    if echo "$last" | grep -q "died"; then
        echo "  ✅ $desc — died is last line"
    else
        echo "  ❌ $desc — log after died: $last"
    fi
}

echo "=== invalid args ==="
for cmd in "" "0 800 200 200" "-5 800 200 200" "a b c d" "5 0 200 200"; do
    ./philo $cmd > /dev/null 2>&1 && echo "  ❌ should fail: $cmd" || echo "  ✅ rejected: '$cmd'"
done

echo "=== should die ==="
run_must_die "1 philo, 800ms"     1 800 200 200
run_must_die "4 philos, tight"    4 310 200 100
run_must_die "5 philos, very tight" 5 200 100 100

echo "=== should NOT die ==="
run_no_die "5 800 200 200"   5 800 200 200
run_no_die "4 410 200 200"   4 410 200 200
run_no_die "5 610 200 100"   5 610 200 100
run_no_die "200 800 200 200" 200 800 200 200

echo "=== must_eat ==="
run_must_eat "5 800 200 200 5" 5 800 200 200 5
run_must_eat "4 410 200 200 3" 4 410 200 200 3
run_must_eat "200 800 200 200 2" 200 800 200 200 2

echo "=== output integrity ==="
check_no_log_after_died "4 310 200 100" 4 310 200 100
check_no_log_after_died "5 200 100 100" 5 200 100 100

rm -f /tmp/philo_out
echo "=== done ==="