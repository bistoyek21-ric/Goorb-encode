import subprocess
import sys
from threading import Thread

def run_a_to_b():
    while True:
        data = process_a.stdout.readline()
        if data:
            process_b.stdin.write(data)
            process_b.stdin.flush()

def run_b_to_a():
    while True:
        data = process_b.stdout.readline()
        if data:
            process_a.stdin.write(data)
            process_a.stdin.flush()

if __name__ == "__main__":
    process_a = subprocess.Popen(
        [sys.executable, "a.py"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        text=True,
        bufsize=1,
    )

    process_b = subprocess.Popen(
        [sys.executable, "b.py"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        text=True,
        bufsize=1,
    )

    Thread(target=run_a_to_b, daemon=True).start()
    Thread(target=run_b_to_a, daemon=True).start()

    try:
        process_a.wait()
        process_b.wait()
    except KeyboardInterrupt:
        process_a.terminate()
        process_b.terminate()