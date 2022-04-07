import os
import sys
import time

DIR = os.path.dirname(os.path.realpath(__file__))

sys.path.append(os.path.dirname(DIR))

import media

media.init(800, 600, 'test')

done = False
while not done:
    while True:
        event = media.poll_event()
        if not event: break
        if event == 'q':
            done = True
            break
    media.clear(color=(0, 0, 0))
    text_y = 40
    text_h = 20
    text_x = 10
    media.line(x=0,      y=text_y,        w=100, h=0,   color=(128, 0, 0))
    media.line(x=0,      y=text_y-text_h, w=100, h=0,   color=(0, 0, 128))
    media.line(x=text_x, y=0,             w=0,   h=60,  color=(0, 128, 0))
    media.line(x=700,    y=500,           w=100, h=100, color=(128, 128, 0))
    media.vector_text('''0.123#456$789%!                        \n'''
                      '''abc'def,ghijklmnopqrstuvwxyz           \n'''
                      '''ABC"DEF_GHIJKLMNOPQRSTUVWXYZ           \n'''
                      '''D&D;   a-A+(B/c)*  p|q                 \n'''
                      '''a: b=c<d A>f?  user@email.ca           \n'''
                     '''\\n x[i]^2 `${x}` ~30 {a: 3}            \n'''
                      '''                                       \n'''
                      '''The quick brown fox jumps over the lazy\n'''
                      '''dog.                                   \n'''
                      '''                                       \n'''
                      '''                                       \n'''
                      '''                                       \n'''
                      '''                                       \n'''
                      '''                                      .\n''', x=text_x, y=text_y, h=text_h)
    media.display();
    time.sleep(0.05)
media.close()
