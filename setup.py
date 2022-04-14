from distutils.core import setup, Extension
def main():
    setup(name='winhook',
          version='0.1',
          description='windows hooking thingy i think',
          author='omegalol21',
          author_email='none@none.none',
          include_dirs=['src/include'],
          ext_modules=[Extension('winhook', ['src/py/winhook.c'], libraries=['user32', 'dwmapi'])])

if __name__ == '__main__':
    main()