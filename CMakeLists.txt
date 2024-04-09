cmake_minimum_required(VERSION 3.27)

project(ShellZ VERSION 1.0 LANGUAGES C)

add_executable(ShellZ
    src/token.c src/token.h
    src/lexer.c src/lexer.h
    src/command.c src/command.h
    src/parser.c src/parser.h
    src/runner.c src/runner.h
    src/errors.c src/errors.h
    src/main.c
)
