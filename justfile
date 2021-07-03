init:
    meson build

build:
    meson compile -C build

test:
    meson test -v -C build
