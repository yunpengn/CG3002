# Software Component

We are using [Pipenv](https://pipenv.readthedocs.io/) to manage our dependencies, which is the latest tool in Python's world that combines the abilities of [pip](https://pypi.org/project/pip/) and [virtualenv](https://virtualenv.pypa.io/).

## Installation of [Pipenv](https://pipenv.readthedocs.io/)

_Notice: The guide below is for MacOS only._

- Make sure you have Python installed.
```bash
python --version
```
or
```bash
python3 --version
```
- Make sure you have pip installed.
```bash
pip --version
```
or
```bash
pip3 --version
```
- Make sure you have [Homebrew]() installed.
```bash
brew -v
```
- Install Pipenv now.
```bash
brew install pipenv
```

## Using [Pipenv](https://pipenv.readthedocs.io/)

- Sometimes, locale shell variable could cause problems. If so, you may want to add the following lines to the end of `~/.bash_profile`.
```bash
export LANG=en_US.UTF-8
export LC_ALL=en_US.UTF-8
```
- To install a new dependency, such as `scikit-learn`, run
```bash
pipenv install scikit-learn
```
- To use the packages installed, run
```bash
pipenv run python XXX.py
```
- Alternatively, you can spawn a new shell under an environment such that all dependencies are loaded
```bash
pipenv shell
```

## Style Guide & Standard

We will strictly follow Python's official style guide as specified [here](https://www.python.org/dev/peps/pep-0008/). Why? Because [Guido van Rossum](https://en.wikipedia.org/wiki/Guido_van_Rossum) thinks so.

- Use 4 spaces per indentation level (spaces are the preferred indentation method).
- 2 blank lines between import statements and class name line.
