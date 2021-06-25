import subprocess

executable = "./main"
error_code = 256 - 1

assert subprocess.check_output([executable, "1 + 1"]) == b"2"
assert subprocess.check_output([executable, "2 * 2"]) == b"4"
assert subprocess.check_output([executable, "2 * 2 + 1"]) == b"5"
assert subprocess.check_output([executable, "2 * 2 - 1"]) == b"3"
assert subprocess.check_output([executable, "   2*2   -1"]) == b"3"

try:
    subprocess.check_call([executable, "   2*"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
except subprocess.CalledProcessError as e:
    assert e.returncode == error_code

try:
    subprocess.check_call([executable, "   2+"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
except subprocess.CalledProcessError as e:
    assert e.returncode == error_code

try:
    subprocess.check_call([executable, "1-1+"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
except subprocess.CalledProcessError as e:
    assert e.returncode == error_code

assert subprocess.check_call([executable, "   2+1"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL) == 0

print("tests ok")