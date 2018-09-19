# Software Component

We are using [Pipenv](https://pipenv.readthedocs.io/) to manage our dependencies, which is the latest tool in Python's world that combines the aabilities of [pip](https://pypi.org/project/pip/) and [virtualenv](https://virtualenv.pypa.io/).

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
