# DaihonCompiler

Tool to compile Daihon formatted text into html

## What is Daihon format?

_Daihon_ means "script for drama" in Japanese.

Daihon format will enable you to write _daihon_ more easily and more quickly.

## Installation

1. Install tools

    ``` bash
    sudo apt install git gcc make
    ```

1. Build & install

    ``` bash
    git clone https://github.com/e-johnnis/DaihonCompiler.git
    cd DaihonCompiler
    make
    sudo make install
    ```

## Usage

- Compile Daihon formatted text into html.  Html text will be exported via stdout.

    ``` bash
    dhnc sample.dhn
    ```

- With option _-o_, text will be exported as a file.

    ``` bash
    dhnc -o sample.html sample.dhn
    ```

- Set html lang with option _-r_

    ``` bash
    dhnc -r ja -o sample.html sample.dhn
    ```

- Set font-family with option _-f_

    ``` bash
    dhnc -f "TakaoGothic" -o sample.html sample.dhn
    ```

## Daihon format scripting