import glob
import os
import shutil
import subprocess
import sys

LOC=os.path.dirname(os.path.realpath(__file__))
os.chdir(LOC)

def invoke(*args): subprocess.check_call(args)

def copy_into(path):
	shutil.copyfile(path, os.path.join('danssfmlpy', os.path.basename(path)))

os.makedirs('built', exist_ok=True)
os.chdir('built')
invoke('cmake', os.path.join('..', '..'))
invoke('cmake', '--build', '.')
os.chdir('..')

copy_into(os.path.join('..', 'media.py'))
copy_into(os.path.join('..', 'controls.py'))
copy_into(glob.glob(os.path.join('built', '*DansSfmlWrapper.*'))[0])

invoke('python3', 'setup.py', 'bdist_wheel', '--plat-name', {
	'linux': 'manylinux1_x86_64',
	'darwin': 'macosx_10_6_intel',
}[sys.platform])
invoke('twine', 'upload', 'dist/*')
