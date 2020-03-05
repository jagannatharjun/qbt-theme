# qbt-theme

## Tool to crate .qbttheme files for [qBittorrent](https://www.qbittorrent.org/).

### Requirements

- [rcc](https://pypi.org/project/PySide2/) to compile `.qres` binary resource files
  - on Windows rcc.exe should be added to the PATH (`pip show PySide2` to get the installation path)

#### For development

- [qtsass](https://pypi.org/project/qtsass/) to compile SCSS

### Usage

#### Get help

``` sh
$ python make-resource.py -h
```

### Compile `material-white/stylesheet.scss` to `stylesheet.qss`

``` sh
$ cd material-white
$ python
>>> import qtsass
>>> qtsass.compile_filename('stylesheet.scss', 'stylesheet.qss')
```


#### Compile the `ubuntu` theme to a file called `test.qbtheme`

``` sh
$ python make-resource.py -s a -o test files ubuntu/*
```
