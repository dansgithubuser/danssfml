import ctypes
import glob
import os
import pprint
import sys

HOME=os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(HOME, '..', 'deps', 'obvious'))

import obvious

sfml=obvious.load_lib('DansSfmlWrapper', ['.', os.path.join('..', 'built')])
def set_ffi_types(ff, restype=None, *argtypes):
	conversions={
		int: ctypes.c_int,
		float: ctypes.c_float,
		str: ctypes.c_char_p,
	}
	ff.restype=conversions.get(restype, restype)
	ff.argtypes=[conversions.get(i, i) for i in argtypes]
set_ffi_types(sfml.dans_sfml_wrapper_init, int, int, int, str)
set_ffi_types(sfml.dans_sfml_wrapper_poll_event, str)
set_ffi_types(sfml.dans_sfml_wrapper_set_vertices_type, None, str)
set_ffi_types(sfml.dans_sfml_wrapper_vertex, None, float, float, int, int, int, int)
set_ffi_types(sfml.dans_sfml_wrapper_draw_vertices)
set_ffi_types(sfml.dans_sfml_wrapper_text_draw, None, float, float, int, str, int, int, int, int)
set_ffi_types(sfml.dans_sfml_wrapper_text_width, float, int, str)
set_ffi_types(sfml.dans_sfml_wrapper_width, int)
set_ffi_types(sfml.dans_sfml_wrapper_height, int)
set_ffi_types(sfml.dans_sfml_wrapper_display)
def init(width=640, height=480, title=''):
	assert sfml.dans_sfml_wrapper_init(width, height, title.encode())==0

def set_sfml(new_sfml):
	global sfml
	sfml=new_sfml
	sfml.dans_sfml_wrapper_poll_event.restype=ctypes.c_char_p

set_sfml(sfml)

def poll_event(): return sfml.dans_sfml_wrapper_poll_event().decode()
def set_vertices_type(s): sfml.dans_sfml_wrapper_set_vertices_type(s.encode())
def vertex(x, y, r, g, b, a): sfml.dans_sfml_wrapper_vertex(x, y, r, g, b, a)
def draw_vertices(): sfml.dans_sfml_wrapper_draw_vertices()
def width(): return sfml.dans_sfml_wrapper_width()
def height(): return sfml.dans_sfml_wrapper_height()
def display(): sfml.dans_sfml_wrapper_draw_vertices(); sfml.dans_sfml_wrapper_display()

def _xi_yi(**kwargs):
	if 'bounds' in kwargs:
		xi, yi, xf, yf=kwargs['bounds']
	if 'xi' in kwargs:
		xi=kwargs['xi']
		xf=kwargs['xf']
	if 'yi' in kwargs:
		yi=kwargs['yi']
		yf=kwargs['yf']
	if 'x' in kwargs:
		xi=kwargs['x']
		xf=xi+kwargs['w']
	if 'y' in kwargs:
		yi=kwargs['y']
		yf=yi+kwargs['h']
	if kwargs.get('right', False):
		d=xf-xi
		xi-=d
		xf-=d
	if kwargs.get('bottom', False):
		d=yf-yi
		yi-=d
		yf-=d
	if kwargs.get('middle_x', False):
		d=(xf-xi)/2
		xi-=d
		xf-=d
	if kwargs.get('middle_y', False):
		d=(yf-yi)/2
		yi-=d
		yf-=d
	return (xi, yi, xf, yf)

def _color(**kwargs):
	r=kwargs.get('r', 255)
	g=kwargs.get('g', 255)
	b=kwargs.get('b', 255)
	a=kwargs.get('a', 255)
	c=kwargs.get('color', ())
	if   len(c)==3: r, g, b   =c
	elif len(c)==4: r, g, b, a=c
	return (r, g, b, a)

def text(s, **kwargs):
	kwargs['xf']=0
	kwargs['w' ]=0
	xi, yi, xf, yf=_xi_yi(**kwargs)
	r, g, b, a=_color(**kwargs)
	sfml.dans_sfml_wrapper_text_draw(xi, yi, yf-yi, s.encode(), r, g, b, a)

def fill(**kwargs):
	set_vertices_type('triangles')
	xi, yi, xf, yf=_xi_yi(**kwargs)
	r, g, b, a=_color(**kwargs)
	vertex(xi, yi, r, g, b, a)
	vertex(xf, yi, r, g, b, a)
	vertex(xi, yf, r, g, b, a)
	vertex(xi, yf, r, g, b, a)
	vertex(xf, yi, r, g, b, a)
	vertex(xf, yf, r, g, b, a)

def line(**kwargs):
	set_vertices_type('lines')
	xi, yi, xf, yf=_xi_yi(**kwargs)
	r, g, b, a=_color(**kwargs)
	vertex(xi, yi, r, g, b, a)
	vertex(xf, yf, r, g, b, a)

def clear(**kwargs):
	fill(x=0, y=0, w=width(), h=height(), color=_color(**kwargs))
	draw_vertices()
