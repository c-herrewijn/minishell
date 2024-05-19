# Minishell | CODAM
'a Unix shell in C'

### Table of Contents
* [Introduction](#introduction)
* [Usage](#usage)
* [Features](#features)
* [Main Concepts](#main-concepts)
* [Observations](#observations)
* [Authors](#authors)

## Introduction
Minishell is a Unix shell in C. It is a simplified version of Bash. \
It is made for an assignement of Codam / 42.

## Usage
Create the minishell executable via `make` \
Run the executable without additional arguments: `./minishell` \
Run UNIX commands like you would do with `bash`

## Features
* execute multiple commands in a pipeline, using the PATH environmental variable or absolute paths
* redirecting inputs and outputs, including heredoc
* custom signal handling, so a signal like SIGINT only terminates the running process, and not the entire shell
* expanding environment variables like `$USER`, and `$?` to get the exit status of the previous command
* a number of [builtins](https://pubs.opengroup.org/onlinepubs/009695399/idx/sbi.html) like `exit`, `echo`, `pwd`, `cd`
* single and double quote handling


## Main Concepts
* **Lexical analysis**, to split the input string into a sequence of tokens, which can be operators or words. Applying the **Finite State Machine** (FSM) model helps to keep in control of all edge cases (e.g. quote handling and operators consisting of multiple chars).
* **Forking** processes, and using **Pipes** to communicate between processes, to create a nice pipeline.
* **Signals**, note EOF is not one

## Observations
* **All commands in a pipeline run parallel.** Some commands, however, will wait for input from the command to its left. For exmaple: `cat | ls` will directly run `ls`, while `cat` is still waiting for input from standard-in.
* **Arguments and redirections don’t need to be in order.** For example: `echo hello > outfile world` will put "hello world" in the outfile.
* **Variable expansion also happens within double quotes.** Variables are expanded outside of quotes or in double quotes, but not in single quotes. For example: `echo "my home folder: $HOME"` will print the home folder location while `echo 'my home folder: $HOME'` will not.
* **Variable expansion is very tolerant of other chars glued to it.** For example `echo ABC$HOME+-` just gives `ABC/Users/<username>+-`
* **Redirections take precedence over pipes.** For example `echo "hello world" > outfile | wc -w` will put “hello world” in the outfile. Since the output is redirected to the file, it will not go into the pipe, so the word count command (`wc`) will receive no input and will return `0`.
* **Pipes and redirection operators don’t need spaces.** For example: `echo "hello world"|wc>outfile` will work fine. This lenience might be surprising, because in if-statements, Bash demands spaces around the square brackets and the `==`. For example in a case like: `if [ 2 == 2 ]; then echo "equal"; fi`.
* **You can have multiple redirections of the same type.** For example: `echo "hello world" > outfile > outfile2 > outfile3` will create all the outfiles, but the echoed text will only go into the last file.
* **Redirections don’t need a command.** For example: `> file1 > file2 > file3` will just create 3 files. Similarly, `< file1 < file2 < file3` will check if all the files exist and have read permissions.
* **exit | exit** won’t exit bash, because in a pipeline all commands (including builtins) run in a subshell.
* **Be careful of accidental history expansion.** In Bash version 3.2 the following does not work: `echo "hello!"`. The reason is that the exclamation mark is a special character used for history expansion.

## Authors
Christiaan Herrewijn : https://profile.intra.42.fr/users/cherrewi \
Kevin Kroon : https://profile.intra.42.fr/users/kkroon
