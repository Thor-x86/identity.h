all: clean real_use_case input-terminal.so input-file.so input-repeat.so process-reverse.so process-toggle_case.so process-roll.so output-terminal.so
.PHONY: all clean

clean:
	rm -f real_use_case *.so

real_use_case:
	clang executable.c -o real_use_case

input-terminal.so:
	clang plugin-input-terminal.c -shared -o input-terminal.so

input-file.so:
	clang plugin-input-file.c -shared -o input-file.so

input-repeat.so:
	clang plugin-input-repeat.c -shared -fPIC -o input-repeat.so

process-reverse.so:
	clang plugin-process-reverse.c -shared -o process-reverse.so

process-toggle_case.so:
	clang plugin-process-toggle_case.c -shared -o process-toggle_case.so

process-roll.so:
	clang plugin-process-roll.c -shared -o process-roll.so

output-terminal.so:
	clang plugin-output-terminal.c -shared -o output-terminal.so