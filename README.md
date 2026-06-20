# DaihonCompiler

Tool to compile Daihon formatted text into html

## What is Daihon format?

_Daihon_ means "script for drama" in Japanese.

Daihon format will enable you to write _daihon_ more easily and more quickly.

## How to use

### Installation

1. Install tools

    ``` bash
    sudo apt install git g++ make
    ```

1. Build & install

    ``` bash
    git clone https://github.com/e-johnnis/DaihonCompiler.git
    cd DaihonCompiler
    make
    make install
    ```

1. (optional) Aliasing

    ``` bash
    echo "alias dhnc ~/.local/bin/DaihonCompiler" >> ~/.bashrc
    source ~/.bashrc
    ```

### Useage

- Compile Daihon formatted text into html (a.html)

    ``` bash
    dhnc sample.dhn
    ```

- Change export name with option _-o_

    ``` bash
    dhnc -o sample.html sample.dhn

- Set html lang with option _-r_

    ``` bash
    dhnc -r ja sample.dhn
    ```

- Set html title with option _-t_

    ``` bash
    dhnc -t "sample daihon" sample.dhn
    ```

- Set font-family with option _-f_

    ``` bash
    dhnc -f "TakaoGothic" sample.dhn

## Daihon format scripting