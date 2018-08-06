from setuptools import setup

setup(
	name='danssfmlpy',
	version='1.0.1',
	description='SFML wrapper for Python',
	url='http://github.com/dansgithubuser/danssfml',
	author='danspypiuser',
	author_email='dansonlinepresence@gmail.com',
	license='MIT',
	packages=['danssfmlpy'],
	package_data={
		'': '*DansSfmlWrapper.*',
	},
	install_requires=['obvious'],
	zip_safe=False,
)
