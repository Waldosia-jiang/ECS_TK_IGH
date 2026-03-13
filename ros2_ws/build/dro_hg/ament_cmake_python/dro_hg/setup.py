from setuptools import find_packages
from setuptools import setup

setup(
    name='dro_hg',
    version='0.0.0',
    packages=find_packages(
        include=('dro_hg', 'dro_hg.*')),
)
