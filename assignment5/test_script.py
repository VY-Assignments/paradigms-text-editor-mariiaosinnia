import subprocess

def run_task5(full_input):
    process = subprocess.Popen(
        ["C:\\Users\\Legion\\CLionProjects\\paradigms-text-editor-mariiaosinnia\\cmake-build-debug\\task5.exe"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(full_input)
    return stdout.strip(), stderr.strip()

def test_task5():
    tests = [
        {"input": "2*3-1", "expected_output": "5"},
        {"input": "8/(7+3)", "expected_output": "0.8"},
        {"input": "6*(-6)", "expected_output": "-36"},
        {"input": "pow(5,3)", "expected_output": "125"},
        {"input": "abs(-3)", "expected_output": "3"},
        {"input": "min(max(2,8), pow(3,2))", "expected_output": "8"},
        {"input": "var x = 2 + 3", "expected_output": None},
        {"input": "var y = x * 4", "expected_output": None},
        {"input": "var a = 8", "expected_output": None},
        {"input": "pow(2, 3) + max(4, min(8, 6)) * a - abs(-7)", "expected_output": "49"},
        {"input": "def myfunc(a, b) { max(a, b) + min(a, b) }", "expected_output": None},
        {"input": "myfunc(3, 4)", "expected_output": "7"},
        {"input": "x + y", "expected_output": "25"},
    ]

    full_input = "\n".join([t["input"] for t in tests]) + "\nexit\n"
    output, error = run_task5(full_input)

    if error:
        print("Runtime error:")
        print(error)
        return

    output_lines = [line.strip() for line in output.split('\n') if line.strip()]
    expected_results = [t for t in tests if t["expected_output"] is not None]

    if len(output_lines) != len(expected_results):
        print("Mismatch in number of results:")
        print("Expected:", len(expected_results))
        print("Got:", len(output_lines))
        print("Output:\n", "\n".join(output_lines))
        return

    for i, test in enumerate(expected_results):
        expected = test["expected_output"]
        actual = output_lines[i]
        if actual != expected:
            print(f"Test failed for input: {test['input']}")
            print(f"Expected: {expected}, Got: {actual}")
            return
        else:
            print(f"Test passed: {test['input']} → {actual}")

    print("All tests passed successfully!")

if __name__ == "__main__":
    test_task5()
