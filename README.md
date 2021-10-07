# minishell
As beautiful as a shell

## 🧐 Description:
A miniture clone of bash.

### Features:
- minishell can run executables from an absolute `/bin/ls`, relative `../../../../../bin/ls`, or environment PATH `ls` with arguments.
- Environment variables are also handled including the return code `$?`.
- You can use redirections `> >> < <<` and pipes `|`.
- Builtins: `cd`, `pwd`, `echo`, `export`, `unset`, `env`, `exit`.
- Single and double quotes work just like in bash, but not for multiline commands.
- Three signals are also handled just like in bash:
  - `Ctrl-C` interrupts a running process or brings up a new prompt.
  - `Ctrl-\` quits from a running program and does nothing on the prompt.
  - `Ctrl-D` throws an EOF or exits minishell.

## 🔧 Usage:
1. Go into the root directory and run `make`.
```
cd minishell
make
```
2. Run the executable created in the output folder.
```
cd output
./minishell
```
<img width="1149" alt="Screen Shot 2021-10-07 at 12 41 16 PM" src="https://user-images.githubusercontent.com/58333462/136377318-c9cc52d2-a4ea-4170-96b7-470c172a1300.png">

### Credit
was a two person project done with [yabdelgh](https://github.com/yabdelgh)

I was responsible for reading input, lexer, parser, environment variable, signals and history.

While yabdelgh took care of command execution.
